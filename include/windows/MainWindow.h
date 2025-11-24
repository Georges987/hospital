#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "Window.h"

class Navigator;

class MainWindow : public Window {
public:
    MainWindow(Navigator& navigator);
    
    void show() override;
    bool handleInput() override;
    std::string getTitle() const override;

private:
    Navigator& navigator;
    void showOptions();
    void showPatientsMenu();
    void showUsersMenu();
};

#endif // MAINWINDOW_H
