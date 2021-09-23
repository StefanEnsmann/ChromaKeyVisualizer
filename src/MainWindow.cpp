#include "MainWindow.h"
#include "WebcamInterface.h"
#include "convertmattowxbmp.h"

#include <wx/panel.h>
#include <wx/menu.h>
#include <wx/stattext.h>
#include <wx/statbox.h>
#include <wx/windowid.h>

bool ChromaKeyVisualizer::OnInit() {
	std::vector<int> availableDevices;
	WebcamInterface::CountCameraDevices(availableDevices);
	MainWindow* frame = new MainWindow(this, availableDevices);
	frame->Show(true);
	return true;
}

wxBEGIN_EVENT_TABLE(MainWindow, wxFrame)
EVT_THREAD(threadNEW_FRAME, MainWindow::SwapBitmaps)
wxEND_EVENT_TABLE()

void MainWindow::SetupUI(std::vector<int>& availableDevices) {
	SetupUI_Menu(availableDevices);
	SetupUI_StatusBar();
	SetupUI_Main();
	Fit();
	Centre();
	Maximize();
}

void MainWindow::SetupUI_Menu(std::vector<int>& availableDevices) {
	wxMenu* menuFile = new wxMenu;
	menuFile->Append(menuID_EXPORT, "Export\tCtrl-E", "Exports the current configuration to a JSON file");
	Bind(wxEVT_MENU, &MainWindow::OnExport, this, menuID_EXPORT);

	menuFile->AppendSeparator();

	menuFile->Append(wxID_EXIT);
	Bind(wxEVT_MENU, &MainWindow::OnExit, this, wxID_EXIT);

	wxMenu* menuCamera = new wxMenu;
	menuCamera->AppendRadioItem(menuID_CAMERA - 1, "No camera\tCtrl-N", "Disable camera processing");
	Bind(wxEVT_MENU, &MainWindow::OnCameraSelect, this, menuID_CAMERA - 1);
	for (int i = 0; i < availableDevices.size(); ++i) {
		int devId = availableDevices[i];
		menuCamera->AppendRadioItem(menuID_CAMERA + devId, "Camera " + std::to_string(devId) + "\tCtrl-" + std::to_string(devId), "Select camera for processing");
		Bind(wxEVT_MENU, &MainWindow::OnCameraSelect, this, menuID_CAMERA + devId);
	}

	wxMenu* menuHelp = new wxMenu;
	menuHelp->Append(menuID_EXPLANATION, "Explanation\tCtrl-X", "Shows an explanation of the underlying system");
	Bind(wxEVT_MENU, &MainWindow::OnExplanation, this, menuID_EXPLANATION);

	menuHelp->AppendSeparator();

	menuHelp->Append(wxID_ABOUT);
	Bind(wxEVT_MENU, &MainWindow::OnAbout, this, wxID_ABOUT);

	wxMenuBar* menuBar = new wxMenuBar;
	menuBar->Append(menuFile, "File");
	menuBar->Append(menuCamera, "Camera");
	menuBar->Append(menuHelp, "Help");

	SetMenuBar(menuBar);
}

void MainWindow::SetupUI_StatusBar() {
	CreateStatusBar();
	SetStatusText("Welcome to wxWidgets!");
}

void MainWindow::SetupUI_Main() {
	wxPanel* mainPanel = new wxPanel(this, wxID_ANY);
	wxFlexGridSizer* mainSizer = new wxFlexGridSizer(1, 2, 0, 0);
	mainSizer->AddGrowableCol(0, 1);
	mainSizer->AddGrowableRow(0, 1);
	mainPanel->SetSizer(mainSizer);

	SetupUI_GLCanvas(mainPanel, mainSizer);
	SetupUI_ControlPanel(mainPanel, mainSizer);
}

void MainWindow::SetupUI_GLCanvas(wxPanel* parent, wxSizer* sizer) {
	//wxGLCanvas* glCanvas = new wxGLCanvas(this);
	//mainSizer->Add(glCanvas, wxSizerFlags(1).Expand());
	wxPanel* tempPanel = new wxPanel(parent, wxID_ANY);
	tempPanel->SetBackgroundColour(wxColour(10, 10, 10));
	sizer->Add(tempPanel, wxSizerFlags(0).Expand());
}

void MainWindow::SetupUI_ControlPanel(wxPanel* parent, wxSizer* sizer) {
	wxBoxSizer* controlPanelSizer = new wxBoxSizer(wxVERTICAL);

	SetupUI_BackgroundColorBox(parent, controlPanelSizer);
	SetupUI_ChromaValues(parent, controlPanelSizer);
	SetupUI_DisplayConfiguration(parent, controlPanelSizer);
	SetupUI_CameraPreview(parent, controlPanelSizer);

	sizer->Add(controlPanelSizer, wxSizerFlags(0).Border(wxALL, 4));
}

void MainWindow::SetupUI_BackgroundColorBox(wxPanel* parent, wxSizer* sizer) {
	wxStaticBoxSizer* backgroundColorBoxSizer = new wxStaticBoxSizer(wxVERTICAL, parent, "Background brightness");

	backgroundSlider = new wxSlider(backgroundColorBoxSizer->GetStaticBox(), uiBACKGROUND_SLIDER, 10, 0, 255);
	backgroundColorBoxSizer->Add(backgroundSlider, wxSizerFlags(1).Expand());

	Bind(wxEVT_SCROLL_CHANGED, &MainWindow::OnBackgroundSliderChanged, this, uiBACKGROUND_SLIDER);

	sizer->Add(backgroundColorBoxSizer, wxSizerFlags(0).Expand().Border(wxALL, 4));
}

void MainWindow::SetupUI_ChromaValues(wxPanel* parent, wxSizer* sizer) {
	wxStaticBoxSizer* chromaValuesSizer = new wxStaticBoxSizer(wxVERTICAL, parent, "Chroma Key filter");

	wxFlexGridSizer* chromaValuesGrid = new wxFlexGridSizer(3, 3, 2, 4);
	chromaValuesGrid->AddGrowableCol(1, 1);

	chromaValuesGrid->Add(new wxStaticText(parent, wxID_ANY, "Color"), wxSizerFlags(0).CenterVertical());
	wxColourPickerCtrl* colorPicker = new wxColourPickerCtrl(parent, uiCHROMACOLOR_PICKER, wxColour(0, 255, 0));
	chromaValuesGrid->Add(colorPicker, wxSizerFlags(0).CenterHorizontal());
	chromaValuesGrid->AddSpacer(0);

	Bind(wxEVT_COLOURPICKER_CHANGED, &MainWindow::OnChromaColorChanged, this, uiCHROMACOLOR_PICKER);

	chromaValuesGrid->Add(new wxStaticText(parent, wxID_ANY, "Similarity"), wxSizerFlags(0).CenterVertical());
	similaritySlider = new wxSlider(parent, uiSIMILARITY_SLIDER, 400, 1, 1000);
	chromaValuesGrid->Add(similaritySlider, wxSizerFlags(0).Expand());
	similaritySpin = new wxSpinCtrl(parent, uiSIMILARITY_SPIN, "400", wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 1, 1000, 400);
	chromaValuesGrid->Add(similaritySpin, wxSizerFlags(0).CenterHorizontal());

	chromaValuesGrid->Add(new wxStaticText(parent, wxID_ANY, "Smoothness"), wxSizerFlags(0).CenterVertical());
	smoothnessSlider = new wxSlider(parent, uiSMOOTHNESS_SLIDER, 80, 1, 1000);
	chromaValuesGrid->Add(smoothnessSlider, wxSizerFlags(0).Expand());
	smoothnessSpin = new wxSpinCtrl(parent, uiSMOOTHNESS_SPIN, "80", wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 1, 1000, 80);
	chromaValuesGrid->Add(smoothnessSpin, wxSizerFlags(0).CenterHorizontal());

	chromaValuesSizer->Add(chromaValuesGrid, wxSizerFlags(0).Expand().Border(wxALL, 8));

	Bind(wxEVT_SCROLL_CHANGED, &MainWindow::OnSimilaritySliderChanged, this, uiSIMILARITY_SLIDER);
	Bind(wxEVT_SPINCTRL, &MainWindow::OnSimilaritySpinChanged, this, uiSIMILARITY_SPIN);

	Bind(wxEVT_SCROLL_CHANGED, &MainWindow::OnSmoothnessSliderChanged, this, uiSMOOTHNESS_SLIDER);
	Bind(wxEVT_SPINCTRL, &MainWindow::OnSmoothnessSpinChanged, this, uiSMOOTHNESS_SPIN);

	sizer->Add(chromaValuesSizer, wxSizerFlags(0).Expand().Border(wxALL, 4));
}

void MainWindow::SetupUI_DisplayConfiguration(wxPanel* parent, wxSizer* sizer) {
	wxStaticBoxSizer* displayConfigurationSizer = new wxStaticBoxSizer(wxVERTICAL, parent, "Display configuration");

	wxFlexGridSizer* mipMappingSizer = new wxFlexGridSizer(1, 3, 2, 4);
	mipMappingSizer->AddGrowableCol(1, 1);
	mipMappingSizer->Add(new wxStaticText(parent, wxID_ANY, "Mip mapping"), wxSizerFlags(0).CenterVertical());
	mipMappingSlider = new wxSlider(parent, uiMIPMAP_SLIDER, 3, 0, 8);
	mipMappingSizer->Add(mipMappingSlider, wxSizerFlags(0).Expand());
	mipMappingSpin = new wxSpinCtrl(parent, uiMIPMAP_SPIN, "3", wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 8, 3);
	mipMappingSizer->Add(mipMappingSpin, wxSizerFlags(0).CenterVertical());
	displayConfigurationSizer->Add(mipMappingSizer, wxSizerFlags(0).Expand().Border(wxALL, 8));

	Bind(wxEVT_SCROLL_CHANGED, &MainWindow::OnMipMappingSliderChanged, this, uiMIPMAP_SLIDER);
	Bind(wxEVT_SPINCTRL, &MainWindow::OnMipMappingSpinChanged, this, uiMIPMAP_SPIN);


	wxBoxSizer* cubeStyleSizer = new wxBoxSizer(wxHORIZONTAL);
	rgbButton = new wxToggleButton(parent, uiRGB_BUTTON, "RGB", wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, wxCheckBoxNameStr);
	rgbButton->SetValue(true);
	cubeStyleSizer->Add(rgbButton, wxSizerFlags(1).Expand());
	ycbcrButton = new wxToggleButton(parent, uiYCBCR_BUTTON, "YCbCr", wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, wxCheckBoxNameStr);
	cubeStyleSizer->Add(ycbcrButton, wxSizerFlags(1).Expand());
	displayConfigurationSizer->Add(cubeStyleSizer, wxSizerFlags(0).Expand().Border(wxALL, 8));

	Bind(wxEVT_TOGGLEBUTTON, &MainWindow::OnCubeStyleChanged, this, uiRGB_BUTTON);
	Bind(wxEVT_TOGGLEBUTTON, &MainWindow::OnCubeStyleChanged, this, uiYCBCR_BUTTON);

	sizer->Add(displayConfigurationSizer, wxSizerFlags(0).Expand().Border(wxALL, 4));
}

void MainWindow::SetupUI_CameraPreview(wxPanel* parent, wxSizer* sizer) {
	wxStaticBoxSizer* cameraPreviewSizer = new wxStaticBoxSizer(wxVERTICAL, parent, "Camera preview");

	webcamPreview = new wxGenericStaticBitmap(parent, wxID_ANY, wxBitmap());
	webcamPreview->Freeze();
	wxSize size = wxSize(webcamWidth, webcamWidth * 9 / 16);
	webcamPreview->SetMinClientSize(size);
	webcamPreview->SetMaxClientSize(size);
	cameraPreviewSizer->Add(webcamPreview, wxSizerFlags(0));

	sizer->Add(cameraPreviewSizer, wxSizerFlags(0).Expand().Border(wxALL, 4));
}

void MainWindow::DisableWebcam() {
	if (thread) {
		thread->ShouldStop();
		thread->Wait();
		delete thread;
	}
	if (webcamBitmapA) {
		delete webcamBitmapA;
	}
	if (webcamBitmapB) {
		delete webcamBitmapB;
	}
	thread = NULL;
	webcamBitmapA = NULL;
	webcamBitmapB = NULL;
	isWebcamBitmapA = true;
}

void MainWindow::ActivateWebcam(int id) {
	thread = new WebcamThread(this, id);
	webcamBitmapA = new wxBitmap(thread->GetWidth(), thread->GetHeight(), 24);
	webcamBitmapB = new wxBitmap(thread->GetWidth(), thread->GetHeight(), 24);
	wxSize size = wxSize(webcamWidth, webcamWidth * thread->GetHeight() / thread->GetWidth());
	webcamPreview->SetMinClientSize(size);
	webcamPreview->SetMaxClientSize(size);

	thread->Run();
}

void MainWindow::SwapBitmaps(wxThreadEvent& event) {
	wxBitmap* currentBitmap = isWebcamBitmapA ? webcamBitmapA : webcamBitmapB;
	cv::Mat* frame = event.GetPayload<cv::Mat*>();
	ConvertMatBitmapTowxBitmap(*frame, *currentBitmap);
	webcamPreview->SetBitmap(*currentBitmap);
	isWebcamBitmapA = !isWebcamBitmapA;
	delete frame;
}