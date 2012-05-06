// Assistive.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace std;
using namespace cv;

int main(int argc, char* argv[])
{
	Mat img = imread("img.jpg");
	namedWindow("Test image");
	imshow("Test image", img);
	waitKey(5000);

	system("pause");
	return 0;
}

