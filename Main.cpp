#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main(int argc, char** argv) {
	Mat frame;
	VideoCapture cap;
	cap.open(0);

	if (!cap.isOpened()) {
		cerr << "ERROR! Unable to open camera!" << endl;
		return -1;
	}

	cout << "Start grabbing" << endl;

	namedWindow("Display window", WINDOW_AUTOSIZE);
	while (true) {
		cap.read(frame);
		imshow("Display window", frame);
		if (waitKey(5) >= 0) {
			break;
		}
	}

	return 0;
}