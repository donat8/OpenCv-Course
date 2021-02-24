#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;



void CroppAndResize() {

	string path = "Resources/test.png";

	Mat img = imread(path);
	Mat imgResize,imgCrop;


	   /// // CROPPING AND RESIZING // ///

	//for size of img
	//cout << img.size() << endl;

	//resize(img, imgResize, Size(640,480));
	//OR
	resize(img, imgResize, Size(),0.5,0.5);  //50% scaling

	//region of interest
	Rect roi(200, 100, 300, 300);
	imgCrop = img(roi);

	imshow("image", img);
	imshow("image resize", imgResize);
	imshow("image cropped", imgCrop);


	waitKey(0);

}