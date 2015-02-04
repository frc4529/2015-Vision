/* 
 * File:   CamFeed.h
 * Author: silvea
 *
 * Feed input (a slightly modified OpenCV VideoCapture with fixed properties)
 *
 * Created on 26 January 2015, 1:57 PM
 */

#ifndef CAMFEED_H
#define	CAMFEED_H

#include <opencv2/highgui/highgui.hpp>

using namespace cv;

class CamFeed : public VideoCapture {
public:
    CamFeed(const char * feedPath);
    CamFeed(int camIndex);
    virtual ~CamFeed();
};

#endif	/* CAMFEED_H */

