/* 
 * File:   Viewer.cpp
 * Author: silvea
 * 
 * Created on 26 January 2015, 2:18 PM
 */

#include "Viewer.h"

using namespace cv;

Viewer::Viewer() : Mat(), name("out") {
    namedWindow(name, 1);
}

Viewer::Viewer(std::string winName) : Mat(), name(winName) {
    namedWindow(name, 1);
}

Viewer::Viewer(const Mat &orig, std::string winName) : Mat(orig), name(winName) {
}

void Viewer::update() {
    imshow(name, *this);
}

Viewer::~Viewer() {
    destroyWindow(name);
}

