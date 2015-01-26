/* 
 * File:   main.cpp
 * Author: silvea
 *
 * Created on 26 January 2015, 1:55 PM
 */

#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "CamFeed.h"
#include "Viewer.h"
#include "TargetDetector.h"

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {
    CamFeed cam;
    
    if (!cam.isOpened())
    {
        cerr << "Error opening capture!" << endl;
        return 1;
    }
    
    Viewer viewer, viewerA("out1"), viewerB("out2");
    
    TargetDetector detector(viewerA);
    
    for (;;) {
        cam >> viewer;
        viewerA = viewer.clone();
        detector.prepareImage();
        detector.findContours();
        viewerB = detector.filterContours();
        
        
        viewer.update();
        viewerA.update();
        viewerB.update();
        
        switch(cv::waitKey(100/3))
        {
            case 'q':
            case 'Q':
                return 0;
        }
    }

    return 0;
}

