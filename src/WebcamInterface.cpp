#include "WebcamInterface.h"
#include <wx/rawbmp.h>

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

wxBitmap* WebcamInterface::OpenCamera(int id, cv::VideoCapture& videoCapture) {
	videoCapture.release();
	videoCapture.open(id);
	if (videoCapture.isOpened()) {
		cv::Mat frame;
		videoCapture.read(frame);
		int width = videoCapture.get(cv::CAP_PROP_FRAME_WIDTH);
		int height = videoCapture.get(cv::CAP_PROP_FRAME_HEIGHT);
		std::cout << frame.type() << std::endl;
		wxBitmap* bitmap = new wxBitmap(width, height);
		return bitmap;
	}
	return (wxBitmap*)0;
}