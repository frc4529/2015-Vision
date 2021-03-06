/* 
 * File:   test.cpp
 * Author: silvea
 *
 * C++ demo of lib usage
 *
 * Created on 1 February 2015, 2:32 PM
 */

#include "VisionLib.h"
#include "stdio.h"

using namespace std;

int main() {
	//InstanceStore * store = initCamera(1);
	InstanceStore * store = initFeed("/home/silvea/Documents/Robotics/2015/OpenCV/sampleVideo/out.flv");
        if (!setThreshold(store, 234)) // Is optional
            return 1;
	LineResult result = processFrame(store);
	while (result.isProcessed)
	{
		if (result.isGood)
		{
			printf("X pos: %.2f, width: %.2f, rotation: %d\n", result.xPos, result.width, result.rotation);
		}
		result = processFrame(store);
	}
	closeCamera(store);
	return 0;
}

