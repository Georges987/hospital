#ifndef CONSULTATIONWINDOW_H
#define CONSULTATIONWINDOW_H

#include "Window.h"
#include "Patient.h"

class Navigator;

class ConsultationWindow : public Window {
public:
    ConsultationWindow(const Patient& patient, Navigator& navigator);
    
    void show() override;
    bool handleInput() override;
    std::string getTitle() const override;
    
private:
    Patient patient;
    Navigator& navigator;
    
    void showConsultations();
    void showOptions();
    void bookConsultation();
    void completeConsultation();
};

#endif // CONSULTATIONWINDOW_H
