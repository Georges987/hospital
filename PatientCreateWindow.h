#ifndef PATIENTCREATEWINDOW_H
#define PATIENTCREATEWINDOW_H

#include "Window.h"
#include <string>

class Navigator;

class PatientCreateWindow : public Window {
public:
    PatientCreateWindow(Navigator& navigator);
    
    void show() override;
    bool handleInput() override;
    std::string getTitle() const override;
    
private:
    Navigator& navigator;
    
    std::string readString(const std::string& prompt);
    int readInt(const std::string& prompt);
};

#endif // PATIENTCREATEWINDOW_H
