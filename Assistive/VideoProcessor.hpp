#pragma once
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/video/tracking.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

#include "Gesture.hpp"

using namespace cv;

enum vpDirection 
{
	DIR_FIX_POS = -1,
	DIR_NONE = 0,
	DIR_LEFT = 1,
	DIR_RIGHT = 2
};

class VideoProcessor
{
public:
	VideoProcessor(void);
	~VideoProcessor(void);
	void processFrame(Mat image);
	RotatedRect getTrackBox();
	Rect getSelection();
	Rect getLeftSelection();
	bool isGestureReady();
	bool isLeftGestureReady();
	Gesture getLeftGesture();
	Gesture getGesture();

private:
	bool mFirstFrame;
	Rect mSelection;
	Rect mLeftSelection;
	RotatedRect mTrackBox;
	Mat mHist;
	Mat backproj;
	Mat hsv, hue, mask;
	Rect trackWindow;
	bool mGestureReady;
	Gesture mGesture;
	Gesture mLeftGesture;
	vpDirection mMovementDirection;
	RotatedRect mFixedTrackBox;
	int frameNo;
	bool mLeftGestureActive;
	bool mLeftGestureReady;
};

