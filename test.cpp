#include "VisionLib.h"
#include "stdio.h"

using namespace std;

/*typedef struct LineResult {
    bool isProcessed, isGood;
    float xPos;
    int width;
    rotation_t rotation;
    
} LineResult;*/

int main() {
	//instanceStore * store = initCamera(0);
	instanceStore * store = initFeed("/home/silvea/Documents/Robotics/2015/OpenCV/sampleVideo/out.flv");
	LineResult result = processFrame(store);
	while (result.isProcessed)
	{
		if (result.isGood)
		{
			printf("X pos: %.2f, width: %d, rotation: %d\n", result.xPos, result.width, result.rotation);
		}
		result = processFrame(store);
	}
	closeCamera(store);
	return 0;
}

