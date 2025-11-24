#ifndef EXPORTWINDOW_H
#define EXPORTWINDOW_H

#include "Window.h"

class Navigator;

class ExportWindow : public Window {
public:
    ExportWindow(Navigator& navigator);
    
    void show() override;
    bool handleInput() override;
    std::string getTitle() const override;
    
private:
    Navigator& navigator;
    
    void showOptions();
};

#endif // EXPORTWINDOW_H
