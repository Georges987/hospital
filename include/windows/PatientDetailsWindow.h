#ifndef PATIENTDETAILSWINDOW_H
#define PATIENTDETAILSWINDOW_H

#include "Window.h"
#include "Patient.h"

class Navigator;

class PatientDetailsWindow : public Window {
public:
    PatientDetailsWindow(const Patient& patient, Navigator& navigator);
    
    void show() override;
    bool handleInput() override;
    std::string getTitle() const override;
    
private:
    Patient patient;
    Navigator& navigator;
    
    void showDetails();
    void showOptions();
};

#endif // PATIENTDETAILSWINDOW_H
