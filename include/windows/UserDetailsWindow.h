#ifndef USERDETAILSWINDOW_H
#define USERDETAILSWINDOW_H

#include "Window.h"
#include "User.h"

class Navigator;

class UserDetailsWindow : public Window {
public:
    UserDetailsWindow(const User& user, Navigator& navigator);
    
    void show() override;
    bool handleInput() override;
    std::string getTitle() const override;
    
private:
    User user;
    Navigator& navigator;
    
    void showDetails();
    void showOptions();
};

#endif // USERDETAILSWINDOW_H
