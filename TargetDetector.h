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

class TargetDetector {
public:
    TargetDetector(Mat &_image);
    virtual ~TargetDetector();
    void prepareImage();
    void findContours();
    Mat filterContours();
    
private:
    Mat &image;
    vector<vector<Point> > contours, validContours;
    vector<Vec4i> hierarchy;

};

#endif	/* TARGETDETECTOR_H */

