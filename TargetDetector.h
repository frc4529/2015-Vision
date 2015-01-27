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
    vector<Point>::iterator ptr;
    int length;
    
    LinePair() : length(0) {}
    LinePair(const LinePair& other) : ptr(other.ptr), length(other.length) {}
    
    LinePair(vector<Point>::iterator ptr, Point offset) : ptr(ptr), length(offset.dot(offset)) {}
    LinePair(vector<Point>::iterator ptr, int length) : ptr(ptr), length(length) {}

    bool operator> (const LinePair& rhs) const {return length > rhs.length;}
    bool operator> (const int& rhs) const {return length > rhs;}
    bool operator< (const LinePair& rhs) const {return length < rhs.length;}
    bool operator< (const int& rhs) const {return length < rhs;}

};

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

