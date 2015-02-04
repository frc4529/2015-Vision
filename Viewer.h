/* 
 * File:   Viewer.h
 * Author: silvea
 *
 * UNUSED IN LIBRArY
 * Serves as an easy-to-use viewer window for demos (see viewerDemo branch)
 *
 * Created on 26 January 2015, 2:18 PM
 */

#ifndef VIEWER_H
#define	VIEWER_H

#include <opencv2/highgui/highgui.hpp>

using namespace cv;

class Viewer : public Mat {
public:
    Viewer();
    Viewer(std::string winName);
    Viewer(const Mat &orig, std::string winName);
    virtual ~Viewer();
    void update();
    const std::string name;
    using Mat::operator=;
    
private:

};

#endif	/* VIEWER_H */

