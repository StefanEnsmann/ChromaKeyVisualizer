#include "WebcamInterface.h"

void WebcamInterface::CountCameraDevices(std::vector<int>& cameraIndices) {
	cv::VideoCapture cap;
	for (int i = 0; i < 10; ++i) {
		cap.open(i);
		if (cap.isOpened()) {
			cameraIndices.push_back(i);
		}
		cap.release();
	}
}