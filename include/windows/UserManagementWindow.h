#ifndef USERMANAGEMENTWINDOW_H
#define USERMANAGEMENTWINDOW_H

#include "Window.h"

class Navigator;

class UserManagementWindow : public Window {
public:
    UserManagementWindow(Navigator& navigator);
    
    void show() override;
    bool handleInput() override;
    std::string getTitle() const override;
    
private:
    Navigator& navigator;
    void showOptions();
};

#endif // USERMANAGEMENTWINDOW_H
