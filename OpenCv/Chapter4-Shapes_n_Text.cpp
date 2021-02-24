#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

/// // Draw shapes and text  // ///

void Shapesntext() {

	//Blank image 

	Mat img(512,512,CV_8UC3,Scalar(255,255,255));    //CV_8UC3 is a type, 8 bit unsigned 254, 3 color channels 

	circle(img, Point(256, 256), 155, Scalar(0, 69, 255),FILLED);  //it can be a thick line, change FILLED to 10
	rectangle(img, Point(130, 226), Point(382, 286), Scalar(255, 255, 255),FILLED);
	line(img, Point(130, 296), Point(382, 296), Scalar(255, 255, 255), 2);

	putText(img, "Bleh", Point(137, 262), FONT_HERSHEY_DUPLEX, 0.75, Scalar(0, 69, 255),2);

	imshow("Image", img);

	waitKey(0);

}