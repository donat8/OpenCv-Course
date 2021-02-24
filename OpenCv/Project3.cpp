#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/objdetect.hpp>
#include <iostream>

using namespace cv;
using namespace std;


/// ///     LICENCE PLATE DETECTION     /// ///


void main() {

	VideoCapture cap(0);
	Mat img;

	// loading the cascade file
	CascadeClassifier plateCascade;
	plateCascade.load("Resources/haarcascade_russian_plate_number.xml");

	if (plateCascade.empty()) {cout << "XML file not loaded" << endl;}


	//face detection
	vector<Rect> plates;

	while (true) {
		
		cap.read(img);
		plateCascade.detectMultiScale(img, plates, 1.1, 10);

	//drawing a rect around faces
	for (auto plate : plates) {

		Mat imgCrop = img(plate);
		imshow(to_string(plate.x), imgCrop);
		//we can save it too
		//imwrite("Resources/Plates/"+to_string(plate.x)+".png",imgCrop);
		rectangle(img, plate.tl(), plate.br(), Scalar(255, 0, 255), 3);
	}

		imshow("Image", img);
		waitKey(1);
	}
}