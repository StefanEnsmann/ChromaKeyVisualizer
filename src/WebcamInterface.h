#pragma once
#include "Main.h"
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif
#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>

class WebcamInterface {
public:
	static void CountCameraDevices(std::vector<int>& cameraIndices);
	static wxBitmap* OpenCamera(int id, cv::VideoCapture& videoCapture);
};