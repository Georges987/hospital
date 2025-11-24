#ifndef NAVIGATOR_H
#define NAVIGATOR_H

#include "Window.h"
#include <memory>
#include <stack>

class Navigator {
public:
    Navigator();
    
    // Ajoute une fenêtre à la pile
    void push(std::unique_ptr<Window> window);
    
    // Retire la fenêtre actuelle de la pile
    void pop();
    
    // Boucle principale de l'application
    void run();
    
    // Vérifie si la pile est vide
    bool isEmpty() const;
    
private:
    std::stack<std::unique_ptr<Window>> windowStack;
    bool running;
    
    void clearScreen();
    void showHeader();
};

#endif // NAVIGATOR_H
