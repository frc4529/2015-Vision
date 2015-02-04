#ifndef VIEWER_H
#define	VIEWER_H

/**
 *  @file Viewer.h
 *  GUI viewer for results.
 *  @note This is unused in the library, and useless in the current version.
 *  @note It is only used in the viewerDemo branch.
 */

#include <opencv2/highgui/highgui.hpp>

using namespace cv;

/**
 *  Viewer class.
 *  Extends cv::Mat.
 *  @warning Window name must NOT be the same as another window name within this application.
*/
class Viewer : public Mat {
public:
	/**
	 *	Viewer constructor.
	 *  Uses "out" as the window na,e
	 */
    Viewer();
    /**
     *  Viewer constructor with window name.
     *  @param winName Titlebar/name of window.
     */
    Viewer(std::string winName);
    /**
	 *  Viewer constructor with reference cv::Mat and window name.
	 *  @param orig Const cv::Mat reference to use for the source.
	 *  @param winName Titlebar/name of window.
     */
    Viewer(const Mat &orig, std::string winName);
    /**
	 *  Viewer destructor.
     */
    virtual ~Viewer();
    /**
     *	Refreshes the window.
     *  Data is taken from the inherited cv::Mat.
     */
    void update();
    /**
	 *  Read-only window name.
     */
    const std::string name;
    using Mat::operator=;
    
private:

};

#endif	/* VIEWER_H */

