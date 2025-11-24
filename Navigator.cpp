#include "Navigator.h"
#include <iostream>

Navigator::Navigator() : running(true) {}

void Navigator::push(std::unique_ptr<Window> window) {
    windowStack.push(std::move(window));
}

void Navigator::pop() {
    if (!windowStack.empty()) {
        windowStack.pop();
    }
    
    if (windowStack.empty()) {
        running = false;
    }
}

void Navigator::run() {
    while (running && !windowStack.empty()) {
        clearScreen();
        showHeader();
        
        Window* currentWindow = windowStack.top().get();
        currentWindow->show();
        
        bool shouldContinue = currentWindow->handleInput();
        
        if (!shouldContinue) {
            pop();
        }
    }
    
    std::cout << "\nApplication terminée. Au revoir !" << std::endl;
}

bool Navigator::isEmpty() const {
    return windowStack.empty();
}

void Navigator::clearScreen() {
    // Clear screen (compatible Linux/Mac/Windows)
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void Navigator::showHeader() {
    if (!windowStack.empty()) {
        std::cout << "=== " << windowStack.top()->getTitle() << " ===" << std::endl;
        std::cout << std::endl;
    }
}
