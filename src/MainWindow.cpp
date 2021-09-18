#include "MainWindow.h"

bool ChromaKeyVisualizer::OnInit() {
	MainWindow* frame = new MainWindow();
	frame->Show(true);
	return true;
}

MainWindow::MainWindow() : wxFrame(NULL, wxID_ANY, "Hello World") {
	wxMenu* menuFile = new wxMenu;
	menuFile->Append(ID_Hello, "&Hello...\tCtrl-H", "Help string shown in status bar for this menu item");
	menuFile->AppendSeparator();
	menuFile->Append(wxID_EXIT);

	wxMenu* menuHelp = new wxMenu;
	menuHelp->Append(wxID_ABOUT);

	wxMenuBar* menuBar = new wxMenuBar;
	menuBar->Append(menuFile, "&File");
	menuBar->Append(menuHelp, "&Help");

	SetMenuBar(menuBar);

	CreateStatusBar();
	SetStatusText("Welcome to wxWidgets!");

	Bind(wxEVT_MENU, &MainWindow::OnHello, this, ID_Hello);
	Bind(wxEVT_MENU, &MainWindow::OnAbout, this, wxID_ABOUT);
	Bind(wxEVT_MENU, &MainWindow::OnExit, this, wxID_EXIT);


	wxPanel* mainPanel = new wxPanel(this, wxID_ANY);
	wxFlexGridSizer* mainSizer = new wxFlexGridSizer(1, 2, 0, 0);

	mainSizer->AddGrowableCol(0, 1);
	mainSizer->AddGrowableRow(0, 1);

	//wxGLCanvas* glCanvas = new wxGLCanvas(this);
	//mainSizer->Add(glCanvas, wxSizerFlags(1).Expand());
	wxPanel* tempPanel = new wxPanel(mainPanel, wxID_ANY);
	tempPanel->SetBackgroundColour(*wxRED);
	mainSizer->Add(tempPanel, wxSizerFlags(1).Expand());

	wxPanel* controlPanel = new wxPanel(mainPanel, wxID_ANY);
	controlPanel->SetBackgroundColour(*wxBLUE);
	wxBoxSizer* controlPanelSizer = new wxBoxSizer(wxVERTICAL);

	wxPanel* backgroundColorPanel = new wxPanel(controlPanel, wxID_ANY);
	wxBoxSizer* backgroundColorPanelSizer = new wxBoxSizer(wxHORIZONTAL);
	wxStaticText* colorPickerLabel = new wxStaticText(backgroundColorPanel, wxID_ANY, "Background color");
	backgroundColorPanelSizer->Add(colorPickerLabel);
	wxColourPickerCtrl* colorPicker = new wxColourPickerCtrl(backgroundColorPanel, wxID_ANY, *wxGREEN);
	backgroundColorPanelSizer->Add(colorPicker);

	backgroundColorPanel->SetSizer(backgroundColorPanelSizer);
	controlPanelSizer->Add(backgroundColorPanel);

	controlPanel->SetSizer(controlPanelSizer);
	mainSizer->Add(controlPanel, wxSizerFlags(1).Expand());

	mainPanel->SetSizer(mainSizer);
	Centre();
}

void MainWindow::OnExit(wxCommandEvent& event) {
	Close(true);
}

void MainWindow::OnAbout(wxCommandEvent& event) {
	wxMessageBox("This is a wxWidgets Hello World example", "About Hello World", wxOK | wxICON_INFORMATION);
}

void MainWindow::OnHello(wxCommandEvent& event) {
	wxLogMessage("Hello world from wxWidgets!");
}