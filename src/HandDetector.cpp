/* 
 * File:   HandDetector.cpp
 * Author: morwin
 * 
 * Created on 12 травня 2012, 11:00
 */
#include <iostream>

#include "HandDetector.h"

using namespace std;

HandDetector::HandDetector() :
    _storage(cvCreateMemStorage(0)),
    _contours(0),
    _radius(0.0),
    _show_window(true),
    _frame_delay(5),
    _count_frame(0)
{
}

HandDetector::~HandDetector() {
    cvReleaseCapture(&_capture);
    cvReleaseImage(&_img);
    cvReleaseImage(&_gsImage);
    cvReleaseImage(&_img_gray);
    cvDestroyWindow( "MainCamera" );
}

bool HandDetector::Start() {
    if (!_TurnOnCamera())
        return false;

    if (_show_window)
        _CreateWindow();

    if (!_ShowImage())
        return false;

    return true;
}

bool HandDetector::_TurnOnCamera() {
    _capture = cvCreateCameraCapture(-1);
    assert(_capture);
    if (!_capture) {
        cerr << "Turn on camera failed" << endl;
        return false;
    }

    return true;
}

void HandDetector::_CreateWindow() {
    cvNamedWindow("MainCamera", 1);
}

bool HandDetector::_ShowImage() {
    int c = 0;
    for (;;) {
        _img = cvQueryFrame(_capture);
        if (!_img) {
            cerr << "Don't get image from camera" << endl;
            return false;
        }
        _TransformColor();
        if (_FindContours())
        {
            _count_frame++;
            _DrawCircle();
            cvShowImage("MainCamera", _img);
        }
        else
        {
//            cvShowImage("MainCamera", _img);
            _count_frame = 0;
            cv::destroyWindow("MainCamera");
            continue;
        }
        c = cvWaitKey(10);
        if (c == 27 || c == 'q' || c == 'Q')
            break;
        if (_count_frame == 30)
            cout << _count_frame << endl;
    }

    return true;
}

void HandDetector::_TransformColor() {
    _gsImage = cvCreateImage(cvGetSize(_img), 8, 3);
    cvCopy(_img, _gsImage);

    uchar* ptr1;
    ptr1 = (uchar*) (_gsImage->imageData);

    for (int i = 0; i < _gsImage->height; i++)
        for (int j = 0; j < _gsImage->width; j++) {
            if (ptr1[j * 3 + 2 + i * _gsImage->widthStep] > 1.5 *
                    ptr1[j * 3 + 1 + i * _gsImage->widthStep] &&
                    ptr1[j * 3 + 2 + i * _gsImage->widthStep] > 2 *
                    ptr1[j * 3 + i * _gsImage->widthStep]) {
                ptr1[j * 3 + i * _gsImage->widthStep] = 255;
                ptr1[j * 3 + 1 + i * _gsImage->widthStep] = 255;
                ptr1[j * 3 + 2 + i * _gsImage->widthStep] = 255;
            } else {
                ptr1[j * 3 + i * _gsImage->widthStep] = 0;
                ptr1[j * 3 + 1 + i * _gsImage->widthStep] = 0;
                ptr1[j * 3 + 2 + i * _gsImage->widthStep] = 0;
            }
        }
}

bool HandDetector::_FindContours() {
    _img_gray = cvCreateImage(cvSize(_gsImage->width, _gsImage->height), 8, 1);
    _contours = 0;
    _storage = cvCreateMemStorage(0);
    cvCvtColor(_gsImage, _img_gray, CV_BGR2GRAY);
    // REMEMBER: add cvPoint(0, 0) in end if need
    cvFindContours(_img_gray, _storage, &_contours, sizeof (CvContour),
                   CV_RETR_LIST, CV_CHAIN_APPROX_SIMPLE);
    CvSeq* h_next = 0;
    CvSeq* contur = _contours;
    if (contur == 0)
        return false;
    for (; contur != 0; contur = contur->h_next) {
        if (contur != _contours)
            if (h_next->total >= contur->total) {
                h_next->h_next = h_next->h_next->h_next;
                continue;
            }
        h_next = contur;
    }
    if (h_next->total < 250)
        return false;
    cvDrawContours(_gsImage, h_next, CV_RGB(255, 0, 0),
            CV_RGB(0, 255, 0), 2, 2, CV_AA, cvPoint(0, 0));
    cvMinEnclosingCircle(h_next, &_center, &_radius);
    return true;

}
// we draw red circle

void HandDetector::_DrawCircle() {
    if (_center.x>-1) {
        CvPoint p;
        p.x = _center.x;
        p.y = _center.y;
        cvCircle(_img, p, _radius, CV_RGB(255, 0, 0), 3, 8, 0);
    }
}