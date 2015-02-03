/* 
 * File:   CamFeed.cpp
 * Author: silvea
 * 
 * Created on 26 January 2015, 1:57 PM
 */

#include "CamFeed.h"

#if LIVE_FEED
#define FEED_PATH 0
#else
#define FEED_PATH "/home/silvea/Documents/Robotics/2015/OpenCV/sampleVideo/out.flv"
#endif

CamFeed::CamFeed(const char * feedPath) : VideoCapture(feedPath) {
	set(CV_CAP_PROP_FRAME_WIDTH, 320);
	set(CV_CAP_PROP_FRAME_HEIGHT, 240);
	set(CV_CAP_PROP_FPS, 30);
}

CamFeed::CamFeed(int camIndex) : VideoCapture(camIndex) {
	set(CV_CAP_PROP_FRAME_WIDTH, 320);
	set(CV_CAP_PROP_FRAME_HEIGHT, 240);
	set(CV_CAP_PROP_FPS, 30);
}

CamFeed::~CamFeed() {
	if (isOpened())
		release();
}

