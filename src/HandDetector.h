/* 
 * File:   HandDetector.h
 * Author: morwin
 *
 * Created on 12 травня 2012, 11:00
 */

#pragma once

#include <cv.h>
#include <highgui.h>
#include <cxcore.h>
#include "opencv2/highgui/highgui.hpp"

class HandDetector {
public:
    HandDetector();
    virtual ~HandDetector();

    bool Start();
private:
    //Turn on and check camera
    bool _TurnOnCamera();
    // Create window in and show image
    void _CreateWindow();
    //Getting orange image
    bool _ShowImage();
    //Get image in graystyle
    void _TransformColor();
    //
    bool _FindContours();
    // Draw border
    void _DrawCircle();
    //Destruct all images
    void _ReleaseImage();
    CvCapture* _capture;
    IplImage* _img;
    IplImage* _gsImage;
    IplImage* _binImage;
    IplImage* _img_gray;

    CvMemStorage* _storage;
    CvSeq* _contours;
    CvPoint2D32f _center;
    float _radius;
    
    bool _show_window;
    int _frame_delay;
    
    unsigned int _count_frame;
};