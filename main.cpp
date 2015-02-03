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
int main() {
    CamFeed cam("/home/silvea/Documents/Robotics/2015/OpenCV/sampleVideo/out.flv");
    
    if (!cam.isOpened())
    {
        cerr << "Error opening capture device/file!" << endl;
        return 1;
    }
    
    Viewer viewer, viewerA("out1");
    
    TargetDetector detector(viewerA);
    
    for (;;) {
        cam >> viewer;
        if (!viewer.data)
            return 0;
        
        viewerA = viewer.clone();
        detector.prepareImage();
        detector.findContours();
        if (detector.filterContours())
        {
            LineResult detectionResult = detector.getContours();
            cout << "Is good: " << detectionResult.isGood << endl;
            cout << "X pos: " << detectionResult.xPos << ", Width: " << detectionResult.width << ", Rotation: ";
            switch (detectionResult.rotation)
            {
                case NONE:
                    cout << "NONE";
                    break;
                case CLOCKWISE:
                    cout << "CLOCKWISE";
                    break;
                case ANTICLOCKWISE:
                    cout << "ANTICLOCKWISE";
                    break;
            }
            cout << endl;
        }
        
        viewer.update();
        viewerA.update();
        
        
        switch(cv::waitKey(100/3))
        {
            case 'q':
            case 'Q':
                return 0;
        }
    }

    return 0;
}

