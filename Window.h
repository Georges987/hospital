#ifndef WINDOW_H
#define WINDOW_H

#include <string>

class Window {
public:
    virtual ~Window() = default;
    
    // Affiche le contenu de la fenêtre
    virtual void show() = 0;
    
    // Gère l'input utilisateur
    // Retourne false si la fenêtre doit être fermée (pop)
    virtual bool handleInput() = 0;
    
    // Retourne le titre de la fenêtre
    virtual std::string getTitle() const = 0;
};

#endif // WINDOW_H
