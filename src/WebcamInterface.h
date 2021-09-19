#pragma once
#include "Main.h"
#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>

class WebcamInterface {
public:
	static void CountCameraDevices(std::vector<int>& cameraIndices);
};