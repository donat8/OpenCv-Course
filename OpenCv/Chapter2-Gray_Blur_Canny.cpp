#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;


/// ///     Basic functions      /// ///


void Chapter2() {

	string path = "Resources/test.png";

	//matrix datatype
	Mat img = imread(path); 
	Mat imgGray;
	Mat imgBlur;
	Mat imgCanny;
	Mat imgDil, imgErode;

	//color change
	cvtColor(img, imgGray, COLOR_BGR2GRAY);
	//blur
	GaussianBlur(imgGray, imgBlur, Size(7, 7), 5, 0);
	//edge detection, we commonly blur before this
	Canny(imgBlur, imgCanny, 25, 75);

	//increasing or decreasing of edges
	Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3));  //increase = dilate/erode more
	dilate(imgCanny, imgDil, kernel);
	erode(imgDil, imgErode, kernel);

	imshow("Image", img);
	imshow("Image Gray", imgGray);
	imshow("Image blur", imgBlur);
	imshow("Image canny", imgCanny);
	imshow("Image dilation", imgDil);
	imshow("Image erode", imgErode);

	waitKey(0);

}