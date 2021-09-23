#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "Main.h"
#include "WebcamInterface.h"

#include <wx/slider.h>
#include <wx/spinctrl.h>
#include <wx/frame.h>
#include <wx/glcanvas.h>
#include <wx/clrpicker.h>
#include <wx/spinctrl.h>
#include <wx/tglbtn.h>
#include <wx/event.h>
#include <wx/generic/statbmpg.h>
#include <wx/panel.h>

#include <vector>

/// <summary>
/// The main application
/// </summary>
class ChromaKeyVisualizer : public wxApp {
public:
	/// <summary>
	/// Initializes the application and creates a MainWindow
	/// </summary>
	/// <returns>bool to indicate successful initialization</returns>
	virtual bool OnInit();
};

class MainWindow : public wxFrame {
public:
	MainWindow(ChromaKeyVisualizer* app, std::vector<int>& availableDevices) : wxFrame(NULL, wxID_ANY, "Chroma Key Visualizer") {
		this->app = app;
		SetupUI(availableDevices);
	}
private:
	ChromaKeyVisualizer* app;

	wxSlider* backgroundSlider;

	wxSlider* similaritySlider;
	wxSpinCtrl* similaritySpin;

	wxSlider* smoothnessSlider;
	wxSpinCtrl* smoothnessSpin;

	wxSlider* mipMappingSlider;
	wxSpinCtrl* mipMappingSpin;

	wxToggleButton* rgbButton;
	wxToggleButton* ycbcrButton;

	WebcamThread* thread;
	wxBitmap* webcamBitmapA;
	wxBitmap* webcamBitmapB;
	bool isWebcamBitmapA = true;
	wxGenericStaticBitmap* webcamPreview;
	int webcamWidth = 250;

	void SetupUI(std::vector<int>& availableDevices);
	void SetupUI_Menu(std::vector<int>& availableDevices);
	void SetupUI_StatusBar();
	void SetupUI_Main();
	void SetupUI_GLCanvas(wxPanel* parent, wxSizer* sizer);
	void SetupUI_ControlPanel(wxPanel* parent, wxSizer* sizer);
	void SetupUI_BackgroundColorBox(wxPanel* parent, wxSizer* sizer);
	void SetupUI_ChromaValues(wxPanel* parent, wxSizer* sizer);
	void SetupUI_DisplayConfiguration(wxPanel* parent, wxSizer* sizer);
	void SetupUI_CameraPreview(wxPanel* parent, wxSizer* sizer);

	void OnExport(wxCommandEvent& event);
	void OnExit(wxCommandEvent& event);
	void OnCameraSelect(wxCommandEvent& event);
	void OnExplanation(wxCommandEvent& event);
	void OnAbout(wxCommandEvent& event);

	void OnBackgroundSliderChanged(wxScrollEvent& event);
	void OnChromaColorChanged(wxColourPickerEvent& event);
	void OnSimilaritySliderChanged(wxScrollEvent& event);
	void OnSimilaritySpinChanged(wxSpinEvent& event);
	void OnSmoothnessSliderChanged(wxScrollEvent& event);
	void OnSmoothnessSpinChanged(wxSpinEvent& event);
	void OnMipMappingSliderChanged(wxScrollEvent& event);
	void OnMipMappingSpinChanged(wxSpinEvent& event);
	void OnCubeStyleChanged(wxCommandEvent& event);

	void DisableWebcam();
	void ActivateWebcam(int id);
	void SwapBitmaps(wxThreadEvent& event);

	wxDECLARE_EVENT_TABLE();
};

enum MenuID {
	menuID_EXPORT = 1,
	menuID_EXPLANATION = 2,
	menuID_CAMERA = 10
};

enum UIID {
	uiBACKGROUND_SLIDER = 20,
	uiCHROMACOLOR_PICKER = 30,
	uiSIMILARITY_SLIDER = 40,
	uiSIMILARITY_SPIN = 41,
	uiSMOOTHNESS_SLIDER = 50,
	uiSMOOTHNESS_SPIN = 51,
	uiMIPMAP_SLIDER = 60,
	uiMIPMAP_SPIN = 61,
	uiRGB_BUTTON = 70,
	uiYCBCR_BUTTON = 71
};
#endif