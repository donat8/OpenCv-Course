#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

 ///     Importing images     /// ///

Mat imgOriginal, imgGray,imgBlur, imgCanny, imgThre, imgDil, imgErode,imgWarp, imgCrop;
vector<Point> initialPoints, docPoints;

Mat preProcessing(Mat img) {

	//color change
	cvtColor(img, imgGray, COLOR_BGR2GRAY);
	//blur
	GaussianBlur(imgGray, imgBlur, Size(3, 3), 7, 0);
	//edge detection, we commonly blur before this
	Canny(imgBlur, imgCanny, 25, 75);

	//increasing or decreasing of edges
	Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3));  //increase = dilate/erode more
	dilate(imgCanny, imgDil, kernel);
	//erode(imgDil, imgErode, kernel);
	return imgDil;
}

vector<Point> getContours(Mat imgDil) {

	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;

	findContours(imgDil, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

	/*drawContours(img, contours, -1, Scalar(255, 0, 255), 2);*/

	vector<vector<Point>> conPoly(contours.size());
	vector<Rect> boundRect(contours.size());
	string objectType;

	vector<Point> biggest;
	int maxArea=0;

	for (int i = 0; i < contours.size(); i++) {
		int area = contourArea(contours[i]);
		cout << area << endl;



		if (area > 1000) {

			float peri = arcLength(contours[i], true);  //if its closed

			approxPolyDP(contours[i], conPoly[i], 0.02 * peri, true);

			if (area > maxArea && conPoly[i].size()==4) {
				//drawContours(imgOriginal, conPoly, i, Scalar(255, 0, 255), 5);
				biggest = { conPoly[i][0],conPoly[i][1] ,conPoly[i][2] ,conPoly[i][3] };
				maxArea = area;
			}

	
			


			/// drawing 
			//drawContours(imgOriginal, conPoly, i, Scalar(255, 0, 255), 2);

			//rectangle(imgOriginal, boundRect[i].tl(), boundRect[i].br(), Scalar(0, 255, 0), 5);


		}
	}
	return biggest;
}

void drawPoints(vector<Point> points, Scalar color) {

	for (int i = 0; i < points.size(); i++) {
		circle(imgOriginal, points[i],10,color,FILLED);
		putText(imgOriginal, to_string(i), points[i], FONT_HERSHEY_PLAIN, 5, color, 5);
	}
}

vector<Point> reorder(vector<Point> initialPoints) {
	vector<Point> newPoints;
	vector<int> sumPoints,subPoints;

	for(auto point : initialPoints){
		sumPoints.push_back(point.x + point.y);
		subPoints.push_back(point.x - point.y);
	}

	newPoints.push_back(initialPoints[min_element(sumPoints.begin(), sumPoints.end()) - sumPoints.begin()]); //0

	newPoints.push_back(initialPoints[max_element(subPoints.begin(), subPoints.end()) - subPoints.begin()]);  //2
	newPoints.push_back(initialPoints[min_element(subPoints.begin(), subPoints.end()) - subPoints.begin()]);   //3

	newPoints.push_back(initialPoints[max_element(sumPoints.begin(), sumPoints.end()) - sumPoints.begin()]);  //3

	return newPoints;
}

Mat getWarp(Mat img, vector<Point> points, float w, float h) {

	Point2f src[4] = { points[0],points[1],points[2],points[3] };
	Point2f dst[4] = { {0.0f,0.0f},{w,0.0f},{0.0f,h},{w,h} };

	
	Mat matrix = getPerspectiveTransform(src, dst);
	warpPerspective(img, imgWarp, matrix, Point(w, h));
	return imgWarp;
}

void DocumentScanner() {

	string path = "Resources/paper.jpg";

	//matrix datatype
	imgOriginal = imread(path);
	//resize(imgOriginal, imgOriginal, Size(), 0.5, 0.5);

	//preprocessing grayscale and blur
	imgThre=preProcessing(imgOriginal);

	//looking 4 edges - looking for the biggest contour
	initialPoints=getContours(imgThre);
	//drawPoints(initialPoints,Scalar(0,0,255));
	docPoints=reorder(initialPoints);
	//drawPoints(docPoints, Scalar(0, 255, 0));

	//warp
	imgWarp = getWarp(imgOriginal, docPoints, 420, 596);
	//crop
	Rect roi(5, 5, 395, 561);
	imgCrop = imgWarp(roi);

	imshow("Image", imgOriginal);
	//imshow("Image", imgThre);
	imshow("Samo dokument", imgCrop);

	waitKey(0);

}
