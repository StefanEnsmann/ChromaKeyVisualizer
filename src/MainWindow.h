#pragma once
#include "Main.h"

class ChromaKeyVisualizer : public wxApp {
public:
	virtual bool OnInit();
};

class MainWindow : public wxFrame {
public:
	MainWindow();
private:
	wxSlider* backgroundSlider;

	wxSlider* similaritySlider;
	wxSpinCtrl* similaritySpin;

	wxSlider* smoothnessSlider;
	wxSpinCtrl* smoothnessSpin;

	wxSlider* mipMappingSlider;
	wxSpinCtrl* mipMappingSpin;

	wxToggleButton* rgbButton;
	wxToggleButton* ycbcrButton;

	void SetupUI();
	void SetupUI_Menu(int cameraCount);
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

	void OnMipMappingSliderChanged(wxScrollEvent& event);
	void OnMipMappingSpinChanged(wxSpinEvent& event);
	void OnCubeStyleChanged(wxCommandEvent& event);
};

enum MenuID {
	menuID_EXPORT = 1,
	menuID_EXPLANATION = 2,
	menuID_CAMERA = 100
};

enum UIID {
	uiBACKGROUND_SLIDER = 200,
	uiSIMILARITY_SLIDER = 300,
	uiSIMILARITY_SPIN = 301,
	uiSMOOTHNESS_SLIDER = 400,
	uiSMOOTHNESS_SPIN = 401,
	uiMIPMAP_SLIDER = 500,
	uiMIPMAP_SPIN = 501,
	uiRGB_BUTTON = 600,
	uiYCBCR_BUTTON = 601
};