/* 
 * File:   targetDetector.h
 * Author: silvea
 *
 * Created on 26 January 2015, 4:01 PM
 */

#ifndef TARGETDETECTOR_H
#define	TARGETDETECTOR_H

#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;

struct LinePair {
    int length, xPos;
};

#ifdef __cplusplus
extern "C" {
#endif

enum rotation_t {
NONE,
CLOCKWISE,
ANTICLOCKWISE
};

typedef struct LineResult {
    bool isProcessed, isGood;
    float xPos;
    int width;
    rotation_t rotation;
    
} LineResult;

#ifdef __cplusplus
}
#endif

class TargetDetector {
public:
    TargetDetector(Mat &_image);
    virtual ~TargetDetector();
    void prepareImage();
    void findContours();
    bool filterContours();
    LineResult getContours();
    
private:
    Mat &image;
    vector<vector<Point> > contours, validContours;
    vector<Vec4i> hierarchy;
    LineResult result;
    bool shouldFilterContours;

};

#endif	/* TARGETDETECTOR_H */

