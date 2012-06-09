// Assistive.cpp : Defines the entry point for the console application.
//

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/video/tracking.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <iostream>
#include <ctype.h>

#include "VideoProcessor.hpp"
#include "StateKeeper.hpp"

using namespace cv;
using namespace std;

/*VideoCapture initVideo(string file, int camId=-1)
{
	if(camId < 0)
	{
		
	}
}*/

const String PREVIEW_WINDOW_ID = "Preview";
Rect selection;
Point origin;
bool selectObject = false;
Mat image;

void onMouse( int event, int x, int y, int, void* )
{
    if( selectObject )
    {
        selection.x = MIN(x, origin.x);
        selection.y = MIN(y, origin.y);
        selection.width = std::abs(x - origin.x);
        selection.height = std::abs(y - origin.y);

        selection &= Rect(0, 0, image.cols, image.rows);
    }

    switch( event )
    {
    case CV_EVENT_LBUTTONDOWN:
        origin = Point(x,y);
        selection = Rect(x,y,0,0);
        selectObject = true;
        break;
    case CV_EVENT_LBUTTONUP:
        selectObject = false;		
        break;
    }
}

int main(int argc, char* argv[])
{
	//inicjalizacja video
	VideoCapture videoInput;
	videoInput.open("D:/projekt_interfejsy/marcin/gest.avi");

	if(!videoInput.isOpened())
	{
		cout << "***Could not initialize capturing...***\n";
		std::system("pause");
        return 0;
	}

	cv::namedWindow(PREVIEW_WINDOW_ID);

	VideoProcessor videoProcessor;
	StateKeeper stateKeeper;
	cout << stateKeeper.getMainPos() << ":" << stateKeeper.getSubPos() << endl;
	//pêtla odczytywania klatek i wysy³ania ich do przetwarzania
	for(;;)
	{
		Mat frame;
		videoInput >> frame;
		if(frame.empty()) {
			cout << "Escaping loop \n";
			break;
		}

		frame.copyTo(image);
		
		videoProcessor.processFrame(image);
		if(videoProcessor.isGestureReady())
		{
			Gesture gesture = videoProcessor.getGesture();
			cout << "GESTURE FOUND " << gesture.type << endl;
			switch(gesture.type)
			{
			case Gesture::GESTURE_RHAND_LEFT:
				cout << "Keeper: Moving back";
				stateKeeper.moveBackwards();
				cout << stateKeeper.getMainPos() << ":" << stateKeeper.getSubPos() << endl;

				break;
			case Gesture::GESTURE_RHAND_RIGHT:
				cout << "Keeper: Moving forward" << endl;
				stateKeeper.moveForward();
				cout << stateKeeper.getMainPos() << ":" << stateKeeper.getSubPos() << endl;
				break;
			default:
				cout << "Unknown" << endl;
			}
		}

		if(videoProcessor.isLeftGestureReady())
		{
			Gesture gesture = videoProcessor.getLeftGesture();
			cout << "GESTURE FOUND " << gesture.type << endl;
			State* state = stateKeeper.GetState();
			switch(gesture.type)
			{
			case Gesture::GESTURE_LHAND_MOVE:
				if(state->getSubPos() == 1)
				{
					cout << "Keeper: Moving up" << endl;
					stateKeeper.moveUp();
				}
				else if(state->getSubPos() == 0)
				{
					cout << "Keeper: Moving down" << endl;
					stateKeeper.moveDown();
				}
				else
				{
					cout << "Keeper: Executing action" << endl;
					stateKeeper.GetState()->func();
				}
				break;
			default:
				cout << "Unknown" << endl;
				break;
			}
		}

		ellipse( image, videoProcessor.getTrackBox(), Scalar(0,0,255), 3, CV_AA );
		rectangle(image, videoProcessor.getSelection(), Scalar(255, 0, 0), 3, CV_AA);
		rectangle(image, videoProcessor.getLeftSelection(), Scalar(0, 255, 0), 3, CV_AA);
		imshow(PREVIEW_WINDOW_ID, image);
		char c = (char)waitKey(5);
		if(c == 27)
			break;
	}

	Mat img = imread("img.jpg");
	namedWindow("Test image");
	imshow("Test image", img);
	waitKey(500);
	
	system("pause");
	return 0;
}

/*
//inicjalizacja video
	VideoCapture videoInput;
	videoInput.open("D:/projekt_interfejsy/marcin/gest.avi");

	if(!videoInput.isOpened())
	{
		cout << "***Could not initialize capturing...***\n";
		system("pause");
        return 0;
	}

	namedWindow(PREVIEW_WINDOW_ID);
	setMouseCallback( "CamShift Demo", onMouse, 0 );

	selection.x = 319;
	selection.y = 303;
	selection.width = 44;
	selection.height = 44;

	Rect trackWindow;
	float hranges[] = {0,180};
    const float* phranges = hranges;
	int vmin = 10, vmax = 256, smin = 30, hsize = 16;
	Mat hsv, hue, hist, mask, backproj;
	bool firstFrame = true;
	//pêtla odczytywania klatek i wysy³ania ich do przetwarzania
	for(;;)
	{
		Mat frame;
		videoInput >> frame;
		if(frame.empty()) {
			cout << "Escaping loop \n";
			break;
		}

		frame.copyTo(image);
		cvtColor(image, hsv, CV_BGR2HSV);

		inRange(hsv, Scalar(0, smin, MIN(vmin,vmax)),
                    Scalar(180, 256, MAX(vmin, vmax)), mask);

		int ch[] = {0, 0};
		hue.create(hsv.size(), hsv.depth());
		mixChannels(&hsv, 1, &hue, 1, ch, 1);

		if(firstFrame)
		{
			Mat roi(hue, selection), maskroi(mask, selection);
            calcHist(&roi, 1, 0, maskroi, hist, 1, &hsize, &phranges);
			normalize(hist, hist, 0, 255, CV_MINMAX);

			trackWindow = selection;
			firstFrame = false;
		}

		calcBackProject(&hue, 1, 0, hist, backproj, &phranges);
        backproj &= mask;
        RotatedRect trackBox = CamShift(backproj, trackWindow,
                            TermCriteria( CV_TERMCRIT_EPS | CV_TERMCRIT_ITER, 10, 1 ));

		ellipse( image, trackBox, Scalar(0,0,255), 3, CV_AA );
		rectangle(image, selection, Scalar(255, 0, 0), 3, CV_AA);
		imshow(PREVIEW_WINDOW_ID, image);
		char c = (char)waitKey(40);
		if(c == 27)
			break;
	}

*/