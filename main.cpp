/* 
 * File:   main.cpp
 * Author: silvea
 *
 * Created on 26 January 2015, 1:55 PM
 */

#include <iostream>
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
        cerr << "Error opening capture device/file!" << endl;
        return 1;
    }
    
    Viewer viewer, viewerA("out1"), viewerB("out2");
    
    TargetDetector detector(viewerA);
    
    for (;;) {
        cam >> viewer;
        if (!viewer.data)
            return 0;
        
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

