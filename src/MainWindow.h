#pragma once
#include "Main.h"

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif
#include <wx/glcanvas.h>
#include <wx/clrpicker.h>
#include <wx/spinctrl.h>
#include <wx/tglbtn.h>
#include<wx/event.h>

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
	MainWindow(std::vector<int>& availableDevices);
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