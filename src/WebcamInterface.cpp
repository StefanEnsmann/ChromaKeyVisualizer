#include "WebcamInterface.h"
#include "MainWindow.h"
#include <wx/rawbmp.h>
#include <wx/event.h>

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

WebcamThread::WebcamThread(MainWindow* window, int cameraId) : wxThread(wxTHREAD_JOINABLE) {
	this->window = window;
	cap.open(cameraId);
	width = 0;
	height = 0;
	if (cap.isOpened()) {
		cv::Mat frame;
		cap.read(frame);
		width = frame.cols;
		height = frame.rows;
	}
}

wxThread::ExitCode WebcamThread::Entry() {
	while (!shouldStop) {
		cv::Mat* frame = new cv::Mat();
		cap >> *frame;
		wxThreadEvent* event = new wxThreadEvent(wxEVT_THREAD, threadNEW_FRAME);
		event->SetPayload(frame);
		window->GetEventHandler()->QueueEvent(event);
	}
	return static_cast<wxThread::ExitCode>(nullptr);
}