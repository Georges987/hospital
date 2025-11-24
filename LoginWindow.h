#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include "Window.h"
#include <string>

class Navigator;

class LoginWindow : public Window {
public:
    LoginWindow(Navigator& navigator);
    
    void show() override;
    bool handleInput() override;
    std::string getTitle() const override;
    
private:
    Navigator& navigator;
    
    std::string readUsername();
    std::string readPassword();
    void clearScreen();
};

#endif // LOGINWINDOW_H
