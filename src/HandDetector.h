//
// HandDetector.h
//
//     Created: 16.06.2012
//      Author: Misha Sakhnik
//
// This file is part of SmartPc.
//
// SmartPc is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Asf Player License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// SmartPc is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with SmartPc.  If not, see <http://www.gnu.org/licenses/>

#pragma once

#include <cv.h>
#include <highgui.h>
#include <cxcore.h>
#include "opencv2/highgui/highgui.hpp"
#include <vector>

/**
@brief Class for find you gesteurs on webcam
* 
* Provides record and  finding hand
*/
class cHandDetector
{
public:
/**
@brief Construct.
 * 
 This section to initialise variables
*/
    cHandDetector();
/**
@brief Destruct.
 * 
 Release image, destroy window and clear data array
*/
    virtual ~cHandDetector();
/**
@brief Start detecting.
 *
 Turn on camera then create window and showing image on screen.
@return False when cannot create window or turn on camera
 */
    bool Start();
/**
@brief Get array with image data.
@return vector from image data
 */
    std::vector<int> & GetImageArray();
/**
@brief Destroy data.
 * 
 Release image, destroy window and clear data array
 */
    void ReleaseData();
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
    //
    void _CropImage();
    //
    void _ConvertArray();

    CvCapture* _capture;
    IplImage* _img;
    IplImage* _gsImage;
    IplImage* _tmpImage;
    IplImage* _img_gray;

    CvMemStorage* _storage;
    CvSeq* _contours;
    CvPoint2D32f _center;
    float _radius;

    bool _show_window;
    int _frame_delay;

    unsigned int _count_frame;
    std::vector<int> _data;
};