#ifndef MEDICALRECORDWINDOW_H
#define MEDICALRECORDWINDOW_H

#include "Window.h"
#include "Patient.h"

class Navigator;

class MedicalRecordWindow : public Window {
public:
    MedicalRecordWindow(const Patient& patient, Navigator& navigator);
    
    void show() override;
    bool handleInput() override;
    std::string getTitle() const override;
    
private:
    Patient patient;
    Navigator& navigator;
    
    void showMedicalRecord();
    void showOptions();
    void createOrUpdateRecord();
    void assignDoctor();
};

#endif // MEDICALRECORDWINDOW_H
