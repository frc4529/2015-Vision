#ifndef CAMFEED_H
#define	CAMFEED_H

/** @file CamFeed.h
 *  Camera/URI feed.
 *  Provides a camera source.
 */

#include <opencv2/highgui/highgui.hpp>

using namespace cv;

/**
 *  Camera/URI feed.
 *  Provides a camera source.
 */
class CamFeed : public VideoCapture {
public:
	/**
	 *  CamFeed URI constructor.
	 *  Opens up the CamFeed for capture from a specified file path or URI.
	 *  @param feedPath URI/full path of the input file/URI/
	 *  @note For a axis IP camera, try using:
	 *  @code
	 *  http://<USERNAME>:<PASSWORD>@<IP>:<PORT>/axis-cgi/mjpg/video.cgi?resolution=320x240&fps=30&compression=25
	 *  @endcode
	 *  @note See section 2 of http://www.axis.com/files/manuals/vapix_video_streaming_52937_en_1307.pdf for details.
	 */
    CamFeed(const char * feedPath);
    /**
	 *  CamFeed USB camera constructor.
	 *  @param camIndex Index of /dev/videoX for camera to use.
	 */
    CamFeed(int camIndex);
    /** CamFeed destructor. */
    virtual ~CamFeed();
};

#endif	/* CAMFEED_H */

