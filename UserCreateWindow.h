#ifndef USERCREATEWINDOW_H
#define USERCREATEWINDOW_H

#include "Window.h"
#include <string>

class Navigator;

class UserCreateWindow : public Window {
public:
    UserCreateWindow(Navigator& navigator);
    
    void show() override;
    bool handleInput() override;
    std::string getTitle() const override;
    
private:
    Navigator& navigator;
    
    std::string readString(const std::string& prompt);
    int readInt(const std::string& prompt);
};

#endif // USERCREATEWINDOW_H
