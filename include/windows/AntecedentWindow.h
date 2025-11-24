#ifndef ANTECEDENTWINDOW_H
#define ANTECEDENTWINDOW_H

#include "Window.h"
#include "Patient.h"

class Navigator;

class AntecedentWindow : public Window {
public:
    AntecedentWindow(const Patient& patient, Navigator& navigator);
    
    void show() override;
    bool handleInput() override;
    std::string getTitle() const override;
    
private:
    Patient patient;
    Navigator& navigator;
    
    void showAntecedents();
    void showOptions();
    void addAntecedent();
    void toggleAntecedent();
};

#endif // ANTECEDENTWINDOW_H
