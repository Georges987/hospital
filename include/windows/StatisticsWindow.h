#ifndef STATISTICSWINDOW_H
#define STATISTICSWINDOW_H

#include "Window.h"

class Navigator;

class StatisticsWindow : public Window {
public:
    StatisticsWindow(Navigator& navigator);
    
    void show() override;
    bool handleInput() override;
    std::string getTitle() const override;
    
private:
    Navigator& navigator;
    
    void showDashboard();
    void showPatientStats();
    void showProfessionalStats();
    void showMedicalDataStats();
};

#endif // STATISTICSWINDOW_H
