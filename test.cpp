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
	instanceStore * store = initCamera();
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

