#include "VisionLib.h"
#include "Viewer.h"

instanceStore * initCamera()
{
    instanceStore * store;
    store->feed = CamFeed();
    if (!store->feed.isOpened())
    {
        delete &(store->feed);
        delete store;
        return NULL;
    }
    store->detector = new TargetDetector(store->imageStore);
}

LineResult processFrame(instanceStore * store)
{
    
    if (store == NULL)
    {
        LineResult result;
        result.isGood = false;
        return result;
    }
    
    store->feed >> store->imageStore;
    
    if (!store->imageStore.data)
    {
        LineResult result;
        result.isGood = false;
        return result;
    }
    
    store->detector->prepareImage();
    store->detector->findContours();
    if (store->detector->filterContours())
    {
        return store->detector->getContours();
    }
    else
    {
        LineResult result;
        result.isGood = false;
        return result;
    }
}

void closeCamera(instanceStore * store)
{
    if (store == NULL)
        return;
    
    delete store->detector;
    delete &(store->feed);
    delete store;
}