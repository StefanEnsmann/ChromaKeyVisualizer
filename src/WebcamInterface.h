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
#endif