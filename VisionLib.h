/* 
 * File:   VisionLib.h
 * Author: silvea
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
    instanceStore * initCamera();
    LineResult processFrame(instanceStore *);
    void closeCamera(instanceStore *);

#ifdef __cplusplus
}
#endif
#endif	/* VISIONLIB_H */

