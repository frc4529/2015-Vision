#ifndef TARGETDETECTOR_H
#define	TARGETDETECTOR_H

/**
 *  @file TargetDetector.h
 *  Main vision processing code.
 *  Processes frame data and finds the target in the given frame.
 */

#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;

/**
 *  For comparison of lines.
 */
struct LineDetails {
    int length, /**< Length of the line. */
        xPos; /**< The X position of the start point of the line. */
};

#ifdef __cplusplus
extern "C" {
#endif

/**
 *  Rotation direction.
 */
enum rotation_t {
    ANTICLOCKWISE = -1, /**< Rotated anticlockwise */
    NONE = 0, /**< Not rotated */
    CLOCKWISE = 1 /**< Rotated clockwise */
};

/**
 *  Result returned from TargetDetector::getContours()
 */
typedef struct LineResult {
    bool isProcessed, /**< If there was a fatal issue with capturing/processing the frame. */
                      /**< @warning If this is false, you MUST close and re-open the camera, as you will not be able to get any more good frames. */
         isGood; /**< If the target found in the input frame. */
    float xPos; /**< Centeral X position of the target. */
    int width; /**< Combined width of the bounding boxes of the targets. */
               /**< @note Includes space between the 2 bounding boxes of the found targets. */
    rotation_t rotation; /**< Rotation direction of the target. */
} LineResult;

#ifdef __cplusplus
}
#endif

/**
 *  Vision processing/target acquisition code.
 *  Order of calling:
 *    1. prepareImage()
 *    2. findContours()
 *    3. filterContours()
 *    4. getContours()
 */
class TargetDetector {
public:
    /**
     *  TargetDetector constructor.
     *  @param _image Reference to source cv::Mat for processing
    */
    TargetDetector(Mat &_image);
    /**
     *  TargetDetector destructor.
     */
    virtual ~TargetDetector();
    /**
     *  Prepare/threshold input frame.
     *  @note Must be called before running other functions.
     */
    void prepareImage();
    /**
     *  Cleans old data and prepares contour shells via OpenCV.
     *  Clears data from previous the frame, finds contours in the binary image and decimate the found shells.
     */
    void findContours();
    /**
     *  Filter contours to find shells that match the target.
     *  Filters through the found contours, leaving only the contours that match the target.
     *  @returns bool Whether or not you will be able to reliably get contours, according to the number of shells found.
     */
    bool filterContours(); // Check and eliminate invalid contours - if this returns false, this frame doesn't contain the target
    /**
     *  Process and retrieve resulting contours.
     *  Processes filtered contours, returning more specific information about the found target.
     *  @returns LineResult contour data
     *  @note If this was run already on the current frame, it will instantly return the previous result.
     *  @warning If there was an issue with the frame, it will return instantly with LineResult::isProcessed being false, and all other values being old or random data.
     *  @n In this case, you MUST close and attempt to re-open the camera or feed to be able to get a good frame again.
     *  @n You will NOT be able to get any more data otherwise.
     */
    LineResult getContours();
    /**
     *  Threshold value for cuttoff when running prepareImage.
     *  Set by setThreshold().
     *  @note Defaults to 234.
     */
    int thresholdVal;
    
private:
    Mat &image;
    vector<vector<Point> > contours, validContours;
    vector<Vec4i> hierarchy;
    LineResult result;
    bool shouldFilterContours;

};

#endif	/* TARGETDETECTOR_H */

