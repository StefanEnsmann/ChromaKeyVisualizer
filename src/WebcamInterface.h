#ifndef WEBCAMINTERFACE_H
#define WEBCAMINTERFACE_H
#include <wx/thread.h>
#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>

#include <vector>

class MainWindow;

class WebcamInterface {
public:
	static void CountCameraDevices(std::vector<int>& cameraIndices);
};

class WebcamThread : public wxThread {
public:
	WebcamThread(MainWindow* window, int cameraId);
	virtual ExitCode Entry() override;
	int GetWidth() { return width; }
	int GetHeight() { return height; }
	void ShouldStop() { shouldStop = true; }
private:
	MainWindow* window;
	cv::VideoCapture cap;
	int width, height;
	bool shouldStop = false;
};

enum ThreadEventID {
	threadNEW_FRAME = 1000
};
#endif