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
 *  Sets the thresholding cuttoff value.
 *  If not run, the value will default to 234.
 *  @param store Pointer to the store returned by initFeed() or initCamera().
 *  @param newThreshold The new threshold value - takes values 0-255 (inclusive).
 *  @returns true if operation was successful, false if newThreshold was invalid or if store is null.
 *  @note Try to have this as close to 255 as possible while still being able to detect the target reliably.
 *  @note Can be changed multiple times.
 */
bool setThreshold(InstanceStore * store, int newThreshold);
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

