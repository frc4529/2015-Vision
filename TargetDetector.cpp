/* 
 * File:   targetDetector.cpp
 * Author: silvea
 * 
 * Created on 26 January 2015, 4:01 PM
 */

#include "TargetDetector.h"
#include <vector>
#include <iostream>

using namespace std;

TargetDetector::TargetDetector(Mat &_image) : image(_image), thresholdVal(234), shouldFilterContours(false) {
    result.isProcessed = false;
    result.isGood = false;
}

void TargetDetector::prepareImage() {
    cvtColor(image, image, CV_BGR2GRAY);
    // The value 234 may need to be adjusted depending on camera and lighting conditions
    // Try to have this value as close to 255 as possible, while still being able to detect the targets at an adequate distance
    threshold(image, image, thresholdVal, 255, THRESH_BINARY);
}

void TargetDetector::findContours() {
    result.isProcessed = false;
    // Clear old data out
    for (vector<vector<Point> >::iterator it = contours.begin(); it != contours.end(); ++it)
        it->clear();
    contours.clear();
    for (vector<vector<Point> >::iterator it = validContours.begin(); it != validContours.end(); ++it)
        it->clear();
    validContours.clear();
    hierarchy.clear();
    
    // Find contours
    cv::findContours(image, contours, hierarchy, CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));
    
    // Decimate polygons
    for (unsigned int i = 0; i < contours.size(); ++i)
        approxPolyDP(contours[i], contours[i], 6, true);
    
    shouldFilterContours = true;
}

bool TargetDetector::filterContours() {
    // To avoid running twice - only used if running an example
    if (!shouldFilterContours)
        return false;
    
    shouldFilterContours = false;

    // Cancel early if nothing was found
    if (!contours.empty() && !hierarchy.empty())
    {
        for (int idx = 0; idx >= 0; idx = hierarchy[idx][0])
        {
            vector<Point> & contourPnts = contours.at(idx);

            if (hierarchy[idx][3] != -1)
                continue;
            else if (contourPnts.size() != 6)
                continue;

            int anglesFound = 0;

            // Check internal angles between neighbouring lines are within a range of angles to eachother
            for (vector<Point>::iterator it = contourPnts.begin(); it != contourPnts.end(); ++it)
            {
                Point pntBefore = *(it == contourPnts.begin() ? contourPnts.end() - 1 : it - 1);
                Point pntMid = *it;
                Point pntAfter = *(it + 1 == contourPnts.end() ? contourPnts.begin() : it + 1);

                float line1Ang = atan2(pntBefore.y - pntMid.y, pntBefore.x - pntMid.x);
                float line2Ang = atan2(pntAfter.y - pntMid.y, pntAfter.x - pntMid.x);

                float angBetween = fabs(line1Ang - line2Ang);

                if (angBetween >= CV_PI)
                    angBetween = (CV_PI * 2) - angBetween;

                if (angBetween > CV_PI / 3 && angBetween < CV_PI * 2 / 3)
                    anglesFound++;
            }
            // If we have 6 angles within range, add the contour to the list.
            if (anglesFound == 6)
                validContours.push_back(contourPnts);
                
        }
    }
    result.isProcessed = false;
    result.isGood = validContours.size() == 2;
    return result.isGood;
}

LineResult TargetDetector::getContours()
{
    // If we either have already processed the contours, or if we didn't find the required number of shells
    if (result.isProcessed || !result.isGood)
        return result;
    else
        result.isProcessed = true;
    
    int widths[2];
    bool firstWidth = true;
    int minX, maxX;
    for (vector<vector<Point> >::iterator it = validContours.begin(); it != validContours.end(); ++it)
    {
        vector<Point> contour = *it;
        int minXContour = contour[0].x, maxXContour = contour[0].x;
        // We only need to compare 2 veritcal lines for height to get orientation
        LineDetails lines[2];
        int currLineIndex = 2;
        for (vector<Point>::iterator it1 = contour.begin(); it1 != contour.end(); ++it1)
        {
            Point pntA = *it1, pntB = *(it1 + 1 == contour.end() ? contour.begin() : it1 + 1);
            float angBetween = fabs(atan2(pntB.y - pntA.y, pntB.x - pntA.x));

            if (angBetween > CV_PI / 2)
                angBetween = CV_PI - angBetween;

            if (angBetween > CV_PI / 6)
            {
                Point offset = pntB - pntA;
                if (currLineIndex != 0)
                {
                    lines[--currLineIndex].length = offset.dot(offset);
                    lines[currLineIndex].xPos = offset.x;
                }
            }

            if (minXContour > it1->x)
                minXContour = it1->x;
            else if (maxXContour < it1->x)
                maxXContour = it1->x;
        }


        LineDetails smallestLine(lines[0]), largestLine(lines[0]);
        if (lines[1].length > lines[0].length)
            largestLine = lines[1];
        else
            smallestLine = lines[1];
        
        // If this is the first of the 2 targets...
        if (firstWidth)
        {
            widths[0] = minXContour;
            widths[1] = maxXContour - minXContour;
            minX = minXContour;
            maxX = maxXContour;
            firstWidth = false;
        }
        else
        {
            if (minX > minXContour)
                minX = minXContour;
            if (maxX < maxXContour)
                maxX = maxXContour;
            
            // Comparing the widths of the 2 targets for finding rotation
            // The value 3 is the threshold for the rotation to not yet be rotated - 3 pixel difference
            if (abs(widths[1] - (maxXContour - minXContour)) <= 3)
                result.rotation = NONE;
            else if ((widths[0] < minXContour) ^ (widths[1] < (maxXContour - minXContour)))
                result.rotation = ANTICLOCKWISE;
            else
                result.rotation = CLOCKWISE;
        }
    }
    result.xPos = (float)(minX + maxX - image.cols) / 2;
    result.width = maxX - minX;
    return result;
}


TargetDetector::~TargetDetector() {
}

