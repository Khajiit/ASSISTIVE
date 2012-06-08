#include "VideoProcessor.hpp"
#include <iostream>

using namespace cv;

VideoProcessor::VideoProcessor(void)
{
	mFirstFrame = true;

	mMovementDirection = vpDirection::DIR_FIX_POS;

	//TODO: wykrywaæ automatycznie interesujacy obszar selection
	mSelection.x = 319;
	mSelection.y = 303;
	mSelection.width = 44;
	mSelection.height = 44;

	mLeftSelection.x = 306;
	mLeftSelection.y = 21;
	mLeftSelection.width = 140;
	mLeftSelection.height = 100;

	frameNo = 0;
	mLeftGestureActive = false;
}


VideoProcessor::~VideoProcessor(void)
{
}

void VideoProcessor::processFrame(Mat image)
{
	frameNo++;
	//Mat hsv, hue, mask;
	//TODO: przenieœæ to do jakiegoœ configa
	int vmin = 10, vmax = 256, smin = 30, hsize = 16;
	int minDelta = 50;

	float hranges[] = {0,180};
    const float* phranges = hranges;

	//konwersja kolorów z RGB do HSV
	cvtColor(image, hsv, CV_BGR2HSV);

	inRange(hsv, Scalar(0, smin, MIN(vmin,vmax)),
                    Scalar(180, 256, MAX(vmin, vmax)), mask);

	int ch[] = {0, 0};
	hue.create(hsv.size(), hsv.depth());
	mixChannels(&hsv, 1, &hue, 1, ch, 1);

	if(mFirstFrame)
	{
		//obliczenie histogramu œledzonego obszaru
		Mat roi(hue, mSelection), maskroi(mask, mSelection);
        calcHist(&roi, 1, 0, maskroi, mHist, 1, &hsize, &phranges);
		normalize(mHist, mHist, 0, 255, CV_MINMAX);
		mFirstFrame = false;
		trackWindow = mSelection;
	}

	calcBackProject(&hue, 1, 0, mHist, backproj, &phranges);
    backproj &= mask;

	mLeftGestureReady = false;

	Mat myBP;
	//cvtColor(backproj, myBP, CV_HSV2BGR);
	backproj.copyTo(myBP);
	myBP = backproj(mLeftSelection);
	double s = sum(myBP)[0];
	if(s < 700000) 
	{
		mLeftGestureActive = true;
		//std::cout << frameNo << " BOOM " << s << std::endl;
	} else 
	{
		//jezeli by³ aktywy to znaczy, ¿e to koniec zaciskania rêki
		if(mLeftGestureActive)
		{
			mLeftGesture.type = Gesture::GESTURE_LHAND_MOVE;
			mLeftGestureReady = true;
		}
		mLeftGestureActive = false;
	}

    mTrackBox = CamShift(backproj, trackWindow,
                        TermCriteria( CV_TERMCRIT_EPS | CV_TERMCRIT_ITER, 10, 1 ));

	mGestureReady = false;

	//jezeli jeszcze nie zapamietano polozenia srodka to teraz zapamietuje
	if(!mFixedTrackBox.size.width)
	{
		mFixedTrackBox = mTrackBox;
	}

	int delta = mFixedTrackBox.center.y - mTrackBox.center.y;
	if(delta >= minDelta)
	{
		//gest lewy
		if(mGesture.type != Gesture::GESTURE_RHAND_LEFT)
		{
			mGesture.type = Gesture::GESTURE_RHAND_LEFT;
			mGestureReady = true;
		}
	}
	else if((-1*delta) >= minDelta)
	{
		//gest prawy
		if(mGesture.type != Gesture::GESTURE_RHAND_RIGHT)
		{
			mGesture.type = Gesture::GESTURE_RHAND_RIGHT;
			mGestureReady = true;
		}
	}
	else 
	{
		mGesture.type = Gesture::GESTURE_UNKNOWN;
	}

}

/**
* Pobiera ostatnie wykryte po³o¿enie œledzonego obszaru
*/
RotatedRect VideoProcessor::getTrackBox()
{
	return mTrackBox;
}

Rect VideoProcessor::getSelection()
{
	return mSelection;
}

Rect VideoProcessor::getLeftSelection()
{
	return mLeftSelection;
}

bool VideoProcessor::isGestureReady()
{
	return mGestureReady;
}

bool VideoProcessor::isLeftGestureReady()
{
	return mLeftGestureReady;
}

Gesture VideoProcessor::getGesture()
{
	return mGesture;
}

Gesture VideoProcessor::getLeftGesture()
{
	return mLeftGesture;
}