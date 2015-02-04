#ifndef VISIONLIB_H
#define	VISIONLIB_H

/**
 *  @file VisionLib.h
 *  Main library header.
 *  @note More exports are found in TargetDetector.
 */

#include "CamFeed.h"
#include "TargetDetector.h"

/**
 *  Instance of vision system.
*/
class InstanceStore {
public:
	/**
	 *  InstanceStore constructor.
	 *  @param cam CamFeed input source.
	 */
    InstanceStore(CamFeed * cam);
    /**
     *  InstanceStore destructor.
     */
    virtual ~InstanceStore();
    /**
	 *  CamFeed reference.
     */
    CamFeed & feed;
    /**
	 *  cv::Mat for storage of the current frame.
     */
    Mat imageStore;
    /**
     *  TargetDetector instance.
     */
    TargetDetector * detector;
};

#ifdef __cplusplus
extern "C" {
#endif

/**
 *  Starts the vision system from a feed path.
 *  @param feedPath URI of feed source.
 *  @returns InstanceStore for current vision system instance.
 *  @note See CamFeed::CamFeed(const char * feedPath) for details on URI specification.
 */
InstanceStore * initFeed(const char * feedPath);
/**
 *  Starts the vision system with a USB camera.
 *  @param camIndex Index of the camera to use.
 *  @returns InstanceStore for current vision system instance.
 *  @note See CamFeed::CamFeed(int camIndex) for details on camera indexes.
 */
InstanceStore * initCamera(int camIndex);
/**
 *  Process a new frame for vision.
 *  @param store Pointer to the store returned by initFeed() or initCamera().
 *  @returns LineResult Output of vision system.
 */
LineResult processFrame(InstanceStore * store);
/**
 *  Close/release the camera and deallocate all used memory.
 *  @param store Pointer to the store returned by initFeed() or initCamera().
 */
void closeCamera(InstanceStore * store);

#ifdef __cplusplus
}
#endif
#endif	/* VISIONLIB_H */

