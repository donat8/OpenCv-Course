#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/objdetect.hpp>
#include <iostream>

using namespace cv;
using namespace std;


/// ///     face DETECTION     /// ///


void faceDetection() {

	VideoCapture cap(0);
	Mat img;

	// loading the cascade file
	CascadeClassifier faceCascade;
	faceCascade.load("Resources/haarcascade_frontalface_default.xml");

	if (faceCascade.empty()) { cout << "XML file not loaded" << endl; }


	//face detection
	vector<Rect> faces;

	while (true) {

		cap.read(img);
		faceCascade.detectMultiScale(img, faces, 1.1, 10);

		//drawing a rect around faces
		for (auto face : faces) {
			rectangle(img, face.tl(), face.br(), Scalar(255, 0, 255), 3);
		}

		imshow("Image", img);
		waitKey(1);
	}
}