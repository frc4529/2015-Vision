/* 
 * File:   VisionLib.h
 * Author: silvea
 *
 * Main lib header
 * PLEASE NOTE - more externs/exports are in TargetDetector.h
 * They are used internally there, but are returned by the library
 *
 * Created on 1 February 2015, 1:27 PM
 */

#ifndef VISIONLIB_H
#define	VISIONLIB_H

#include "CamFeed.h"
#include "TargetDetector.h"

class instanceStore {
public:
    instanceStore(CamFeed * cam);
    virtual ~instanceStore();
    CamFeed & feed;
    Mat imageStore;
    TargetDetector * detector;
};

#ifdef __cplusplus
extern "C" {
#endif

    instanceStore * initFeed(const char * feedPath);
    instanceStore * initCamera(int camIndex);
    LineResult processFrame(instanceStore *);
    void closeCamera(instanceStore *);

#ifdef __cplusplus
}
#endif
#endif	/* VISIONLIB_H */

