#include "MainWindow.h"

void MainWindow::OnExport(wxCommandEvent& event) {
	wxMessageBox("Export has been toggled", "Press", wxOK | wxICON_INFORMATION);
}

void MainWindow::OnExit(wxCommandEvent& event) {
	Close(true);
}

void MainWindow::OnCameraSelect(wxCommandEvent& event) {
	wxMessageBox("Camera select has been toggled", "Press", wxOK | wxICON_INFORMATION);
}

void MainWindow::OnExplanation(wxCommandEvent& event) {
	wxMessageBox("Explanation has been toggled", "Press", wxOK | wxICON_INFORMATION);
}

void MainWindow::OnAbout(wxCommandEvent& event) {
	wxMessageBox("This is a wxWidgets Hello World example", "About Hello World", wxOK | wxICON_INFORMATION);
}

void MainWindow::OnBackgroundSliderChanged(wxScrollEvent& event) {

}

void MainWindow::OnChromaColorChanged(wxColourPickerEvent& event) {

}

void MainWindow::OnSimilaritySliderChanged(wxScrollEvent& event) {
	similaritySpin->SetValue(event.GetPosition());
}

void MainWindow::OnSimilaritySpinChanged(wxSpinEvent& event) {
	similaritySlider->SetValue(event.GetValue());
}

void MainWindow::OnSmoothnessSliderChanged(wxScrollEvent& event) {
	smoothnessSpin->SetValue(event.GetPosition());
}

void MainWindow::OnSmoothnessSpinChanged(wxSpinEvent& event) {
	smoothnessSlider->SetValue(event.GetValue());
}

void MainWindow::OnMipMappingSliderChanged(wxScrollEvent& event) {
	mipMappingSpin->SetValue(event.GetPosition());
}

void MainWindow::OnMipMappingSpinChanged(wxSpinEvent& event) {
	mipMappingSlider->SetValue(event.GetValue());
}

void MainWindow::OnCubeStyleChanged(wxCommandEvent& event) {
	int id = event.GetId();
	if (id == uiRGB_BUTTON && event.IsChecked()) {
		ycbcrButton->SetValue(false);
	}
	else if (id == uiYCBCR_BUTTON && event.IsChecked()) {
		rgbButton->SetValue(false);
	}
	else if (id == uiRGB_BUTTON && !event.IsChecked()) {
		ycbcrButton->SetValue(true);
	}
	else if (id == uiYCBCR_BUTTON && !event.IsChecked()) {
		rgbButton->SetValue(true);
	}
}