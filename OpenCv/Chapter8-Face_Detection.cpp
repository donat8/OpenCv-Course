#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/objdetect.hpp>
#include <iostream>

using namespace cv;
using namespace std;


/// ///     FACE DETECTION     /// ///


void FaceDetection() {

	string path = "Resources/faces.jpg";

	//matrix datatype
	Mat img = imread(path);   
	resize(img, img, Size(), 0.5, 0.5);

	// loading the cascade file
	CascadeClassifier faceCascade;
	faceCascade.load("Resources/haarcascade_frontalface_default.xml");

	if (faceCascade.empty()) {
		cout << "XML file not loaded" << endl;
	}

	//face detection
	vector<Rect> faces;
	faceCascade.detectMultiScale(img, faces, 1.1, 10);

	//drawing a rect around faces
	for (auto face : faces) {
		rectangle(img, face.tl(), face.br(), Scalar(255, 0, 255), 3);
	}

	imshow("Image", img);
	waitKey(0);

}