#include "VisionLib.h"
#include "Viewer.h"

instanceStore * initCamera()
{
    CamFeed * feed = new CamFeed();
    if (!feed->isOpened())
    {
        delete feed;
        return NULL;
    }
    return new instanceStore(feed);
}

LineResult processFrame(instanceStore * store)
{
    
    if (store == NULL)
    {
        LineResult result;
        result.isProcessed = false;
        return result;
    }
    
    store->feed >> store->imageStore;
    
    if (!store->imageStore.data)
    {
        LineResult result;
        result.isProcessed = false;
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
        result.isProcessed = true;
        result.isGood = false;
        return result;
    }
}

void closeCamera(instanceStore * store)
{
    if (store == NULL)
        return;

    delete store;
}

instanceStore::instanceStore(CamFeed * cam) : feed(*cam)
{
    imageStore.create(240, 320, 0);
    detector = new TargetDetector(imageStore);
}

instanceStore::~instanceStore()
{
    delete detector;
    delete &feed;
}
