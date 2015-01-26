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

TargetDetector::TargetDetector(Mat &_image) : image(_image) {
}


void TargetDetector::prepareImage() {
    cvtColor(image, image, CV_BGR2GRAY);
    threshold(image, image, 234, 256, THRESH_BINARY);
}

void TargetDetector::findContours() {
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
    for (int i = 0; i < contours.size(); ++i)
        approxPolyDP(contours[i], contours[i], 6, true);
}

Mat TargetDetector::filterContours() {
    Mat out(image.rows, image.cols, CV_8UC3, Scalar::all(0));
    int numFound = 0;
    if (!contours.empty() && !hierarchy.empty())
    {
        for (int idx = 0; idx >= 0; idx = hierarchy[idx][0])
        {
            if (hierarchy[idx][3] != -1)
            {
                cout << "Hole" << endl;
                continue;
            }
            if (contours.at(idx).size() != 6)
                continue;

            int anglesFound = 0;

            for (int i = 0; i < contours.at(idx).size(); ++i)
            {
                Point pntBefore = contours.at(idx).at((i - 1) % contours.at(idx).size());
                Point pntMid = contours.at(idx).at(i);
                Point pntAfter = contours.at(idx).at((i + 1) % contours.at(idx).size());

                double line1Ang = atan2(pntBefore.y - pntMid.y, pntBefore.x - pntMid.x);
                double line2Ang = atan2(pntAfter.y - pntMid.y, pntAfter.x - pntMid.x);

                double angBetween = fabs(line1Ang - line2Ang);

                if (angBetween >= CV_PI)
                    angBetween = (CV_PI * 2) - angBetween;

                //cout << line1Ang << " -> " << line2Ang << " -> " << angBetween << endl;

                if (angBetween > CV_PI / 3 && angBetween < CV_PI * 2 / 3)
                {
                    anglesFound++;
                    //cout << line1Ang << " -> " << line2Ang << " -> " << angBetween << endl;
                }
            }
            Scalar color( rand()&255, rand()&255, rand()&255 );
            int drawType = CV_FILLED;
            if (anglesFound != 5)
                continue;
                //drawType = 2;
            else
                validContours.push_back(contours.at(idx));

            drawContours(out, contours, idx, color, drawType, 8, hierarchy);
        }
        numFound = validContours.size();

        if (numFound == 2)
        {
            for (vector<vector<Point> >::iterator it = validContours.begin(); it != validContours.end(); ++it)
            {
                vector<Point> contour = *it;
                Point tl = contour[0], br = contour[0];
                vector<Vec4i> horizontalPnts;
                for (vector<Point>::iterator it1 = contour.begin(); it1 != contour.end(); ++it1)
                {
                    Point pntA = *it1, pntB = *(it1 + 1 == contour.end() ? contour.begin() : it1 + 1);
                    double angBetween = fabs(atan2(pntB.y - pntA.y, pntB.x - pntA.x));

                    if (angBetween > CV_PI / 2)
                        angBetween = CV_PI - angBetween;

                    if (angBetween > CV_PI / 6)
                    {
                        line(out, pntA, pntB, Scalar::all(255), 2);
                        //cout << angBetween << endl;
                        Point offset = pntB - pntA;
                        cout << sqrt(offset.dot(offset)) << endl;
                    }

                    if (tl.x > it1->x)
                        tl.x = it1->x;
                    else if (br.x < it1->x)
                        br.x = it1->x;

                    if (tl.y > it1->y)
                        tl.y = it1->y;
                    else if (br.y < it1->y)
                        br.y = it1->y;
                }
                Point center = (tl + br) * 0.5;
                Rect bounds(tl, br);
                rectangle(out, bounds, Scalar::all(127));
                line(out, tl, center, Scalar::all(255));
                //int dist = bounds.;
                //Point closestPoint = 

                //cout << (double) bounds.height / bounds.width << endl;
            }
        }

    }
    for (int i = 0; i < contours.size(); ++i)
        for (int j = 0; j < contours.at(i).size(); ++j)
            rectangle(out, Rect(contours[i][j].x, contours[i][j].y, 2, 2), Scalar::all(255));
    
    std::stringstream ss;
    if (numFound != 0 && numFound != 2)
    {
        ss.str("");
        ss << "WARNING: ONLY " << numFound << " POLYGONS FOUND!";
        putText(out, ss.str(), Point(2, 26), FONT_HERSHEY_PLAIN, 1, Scalar(0, 0, 255), 1);
    }
    return out;
}


TargetDetector::~TargetDetector() {
}

