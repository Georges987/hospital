#ifndef MAINWINDOW_H
#define MAINWINDOW_H

class MainWindow {
public:
    MainWindow();
    void run();

private:
    void showOptions();
    void handleInput();
    bool running;
};

#endif // MAINWINDOW_H
