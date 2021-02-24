#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;


/// ///     Warp images     /// ///


void WarpImages() {
	
	string path = "Resources/cards.jpg";
	Mat img = imread(path);   

	Point2f src[4] = { {529,142},{771,190},{405,395},{674,457} };
	float w = 250, h = 350;
	Point2f dst[4] = { {0.0f,0.0f},{w,0.0f},{0.0f,h},{w,h} };

	Mat matrix, imgWarp;
	matrix = getPerspectiveTransform(src, dst);
	warpPerspective(img, imgWarp, matrix,Point(w,h));

	/// for circles on points 
	for (int i = 0; i < 4;i++) {
		circle(img, src[i], 10, Scalar(0, 0, 255), 4);
	}


	imshow("Image", img);
	imshow("Image warp", imgWarp);

	waitKey(0);

}