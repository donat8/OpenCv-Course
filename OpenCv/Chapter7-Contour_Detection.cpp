#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;


/// ///     COUNTOURS    /// ///

void getContours(Mat imgDil, Mat img) {

	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;

	findContours(imgDil, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

	/*drawContours(img, contours, -1, Scalar(255, 0, 255), 2);*/

	vector<vector<Point>> conPoly(contours.size());

	vector<Rect> boundRect(contours.size());
	string objectType;

	for (int i = 0; i < contours.size(); i++) {
		int area = contourArea(contours[i]);
		cout << area << endl;

		

		if (area > 1000) {

			float peri = arcLength(contours[i], true);  //if its closed

			approxPolyDP(contours[i], conPoly[i], 0.02 * peri, true);

		

			//how much corner points
			cout<<conPoly[i].size()<<endl;

			boundRect[i]=boundingRect(conPoly[i]);

			

			int objCor = (int)conPoly[i].size();

			if (objCor == 3) { objectType = "Triangle"; }
			if (objCor == 4) { 
				float aspRatio = (float)boundRect[i].width / boundRect[i].height;
				cout << aspRatio << endl;
				if(aspRatio>0.95 && aspRatio<1.05)
					objectType = "Square"; 
				else
					objectType = "Rect"; 
			}
			if (objCor >4) { objectType = "Circle"; }

			/// drawing 
			drawContours(img, conPoly, i, Scalar(255, 0, 255), 2);

			rectangle(img, boundRect[i].tl(), boundRect[i].br(), Scalar(0, 255, 0), 5);

			putText(img, objectType, { boundRect[i].x,boundRect[i].y - 5 }, FONT_HERSHEY_PLAIN, 1, Scalar(0, 69, 255), 1);


		}
	}

}

void ContourDetection() {

	string path = "Resources/shapes.png";

	//matrix datatype
	Mat img = imread(path); 

	/// <summary>
	///  Preprocessing of the immage 
	/// </summary>
	Mat imgGray, imgBlur, imgCanny;
	Mat imgDil;
	//color change
	cvtColor(img, imgGray, COLOR_BGR2GRAY);
	//blur
	GaussianBlur(imgGray, imgBlur, Size(3, 3), 3, 0);
	//edge detection, we commonly blur before this
	Canny(imgBlur, imgCanny, 25, 75);
	//dilation
	Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3));  //increase = dilate/erode more
	dilate(imgCanny, imgDil, kernel);

	getContours(imgDil,img);

	imshow("Image", img);
	//imshow("Image gray", imgGray);
	//imshow("Image blur", imgBlur);
	//imshow("Image canny", imgCanny);
	//imshow("Image dilate", imgDil);
	waitKey(0);

}

