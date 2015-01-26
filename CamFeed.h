/* 
 * File:   CamFeed.h
 * Author: silvea
 *
 * Created on 26 January 2015, 1:57 PM
 */

#ifndef CAMFEED_H
#define	CAMFEED_H
#define LIVE_FEED false

#include <opencv2/highgui/highgui.hpp>

using namespace cv;

class CamFeed : public VideoCapture {
public:
    CamFeed();
    virtual ~CamFeed();
    int getFrameCount() const;
    
private:
#if !LIVE_FEED
    int frameCount;
#endif
};

#endif	/* CAMFEED_H */

