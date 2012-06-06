/* 
 * File:   cHandDetector.cpp
 * Author: morwin
 * 
 * Created on 12 травня 2012, 11:00
 */
#include <iostream>

#include "HandDetector.h"

using namespace std;

cHandDetector::cHandDetector() :
_storage(cvCreateMemStorage(0)),
_contours(0),
_radius(0.0),
_show_window(true),
_frame_delay(5),
_count_frame(0)
{
}

cHandDetector::~cHandDetector()
{
    ReleaseImages();
}

void cHandDetector::ReleaseImages()
{
    cvReleaseCapture(&_capture);
    cvReleaseImage(&_img);
    cvReleaseImage(&_gsImage);
    cvReleaseImage(&_img_gray);
    cvReleaseImage(&_tmpImage);
    cvDestroyWindow("MainCamera");
}

bool cHandDetector::Start()
{
    if (!_TurnOnCamera())
        return false;

    if (_show_window)
        _CreateWindow();

    if (!_ShowImage())
        return false;

    return true;
}

bool cHandDetector::_TurnOnCamera()
{
    _capture = cvCreateCameraCapture(-1);
    assert(_capture);
    if (!_capture)
    {
        cerr << "Turn on camera failed" << endl;
        return false;
    }

    return true;
}

void cHandDetector::_CreateWindow()
{
    cvNamedWindow("MainCamera", 1);
}

bool cHandDetector::_ShowImage()
{
    int c = 0;
    for (;;)
    {
        _img = cvQueryFrame(_capture);
        if (!_img)
        {
            cerr << "Don't get image from camera" << endl;
            return false;
        }
        _TransformColor();
        if (_FindContours())
        {
            _count_frame++;
            _DrawCircle();
            cvShowImage("MainCamera", _gsImage);
        }
        else
        {
            cvShowImage("MainCamera", _img);
            _count_frame = 0;
            cv::destroyWindow("MainCamera");
            continue;
        }
        c = cvWaitKey(10);
        if (c == 27 || c == 'q' || c == 'Q')
            break;
        if (_count_frame == 30)
        {
            _CropImage();
            _ConvertArray();
            return true;
        }
    }

    return false;
}

void cHandDetector::_TransformColor()
{
    _gsImage = cvCreateImage(cvGetSize(_img), 8, 3);
    cvCopy(_img, _gsImage);

    uchar* ptr1;
    ptr1 = (uchar*) (_gsImage->imageData);

    for (int i = 0; i < _gsImage->height; i++)
        for (int j = 0; j < _gsImage->width; j++)
        {
            if (ptr1[j * 3 + 2 + i * _gsImage->widthStep] > 1.5 *
                    ptr1[j * 3 + 1 + i * _gsImage->widthStep] &&
                    ptr1[j * 3 + 2 + i * _gsImage->widthStep] > 2 *
                    ptr1[j * 3 + i * _gsImage->widthStep])
            {
                ptr1[j * 3 + i * _gsImage->widthStep] = 255;
                ptr1[j * 3 + 1 + i * _gsImage->widthStep] = 255;
                ptr1[j * 3 + 2 + i * _gsImage->widthStep] = 255;
            }
            else
            {
                ptr1[j * 3 + i * _gsImage->widthStep] = 0;
                ptr1[j * 3 + 1 + i * _gsImage->widthStep] = 0;
                ptr1[j * 3 + 2 + i * _gsImage->widthStep] = 0;
            }
        }
}

bool cHandDetector::_FindContours()
{
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
    for (; contur != 0; contur = contur->h_next)
    {
        if (contur != _contours)
            if (h_next->total >= contur->total)
            {
                h_next->h_next = h_next->h_next->h_next;
                continue;
            }
        h_next = contur;
    }
    if (h_next->total < 250)
        return false;
    // draw red line from debug
    //cvDrawContours(_gsImage, h_next, CV_RGB(255, 0, 0),
    //        CV_RGB(0, 255, 0), 2, 2, CV_AA, cvPoint(0, 0));
    cvMinEnclosingCircle(h_next, &_center, &_radius);
    return true;

}
// we draw red circle

void cHandDetector::_DrawCircle()
{
    if (_center.x>-1)
    {
        CvPoint p;
        p.x = _center.x;
        p.y = _center.y;
        cvCircle(_img, p, _radius, CV_RGB(255, 0, 0), 3, 8, 0);
    }
}

void cHandDetector::_CropImage()
{
    CvRect rect;
    rect.x = _center.x - _radius;
    rect.y = _center.y - _radius;
    rect.width = _radius * 2;
    rect.height = _radius * 2;
    cvSetImageROI(_gsImage, rect);
    _img->width = 100;
    _img->height = 100;
    _tmpImage = cvCreateImage(cvGetSize(_gsImage),
                              _gsImage->depth,
                              _gsImage->nChannels);
    cvCopy(_gsImage, _tmpImage, NULL);
    cvResize(_tmpImage, _img);
}

void cHandDetector::_ConvertArray()
{
    _data.empty();
    _tmpImage = cvCreateImage(cvSize(_img->height, _img->width), IPL_DEPTH_8U, 1);
    cvCvtColor(_img, _tmpImage, CV_RGB2GRAY);

    for (int i = 0; i < _img->height; ++i)
        for (int j = 0; j < _img->width; ++j)
            _data.push_back(cvGetReal2D(_tmpImage, i, j) ? 1 : 0);
}

vector<int> & cHandDetector::GetImageArray()
{
    return _data;
}