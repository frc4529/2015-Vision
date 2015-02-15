#include "VisionLib.h"
#include "Viewer.h"

InstanceStore * initFeed(const char * feedPath)
{
    CamFeed * feed = new CamFeed(feedPath);
    if (!feed->isOpened())
    {
        delete feed;
        return NULL;
    }
    return new InstanceStore(feed);
}

InstanceStore * initCamera(int camIndex)
{
    CamFeed * feed = new CamFeed(camIndex);
    if (!feed->isOpened())
    {
        delete feed;
        return NULL;
    }
    return new InstanceStore(feed);
}

bool setThreshold(InstanceStore * store, int newThreshold)
{
    if (store == NULL || newThreshold < 0 || newThreshold > 255)
        return false;
    else
    {
        store->detector->thresholdVal = newThreshold;
        return true;
    }
}

LineResult processFrame(InstanceStore * store)
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

void closeCamera(InstanceStore * store)
{
    if (store == NULL)
        return;

    delete store;
}

InstanceStore::InstanceStore(CamFeed * cam) : feed(*cam)
{
    imageStore.create(240, 320, 0);
    detector = new TargetDetector(imageStore);
}

InstanceStore::~InstanceStore()
{
    delete detector;
    delete &feed;
}
