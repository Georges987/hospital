#ifndef LISTWINDOW_H
#define LISTWINDOW_H

#include "Window.h"
#include "Navigator.h"
#include <vector>
#include <functional>
#include <string>
#include <iostream>
#include <limits>

template<typename T>
class ListWindow : public Window {
public:
    using DisplayFormatter = std::function<std::string(const T&)>;
    using ItemSelectedCallback = std::function<void(const T&, Navigator&)>;
    
    ListWindow(
        const std::string& title,
        const std::vector<T>& items,
        DisplayFormatter formatter,
        ItemSelectedCallback callback,
        Navigator& navigator
    );
    
    void show() override;
    bool handleInput() override;
    std::string getTitle() const override;
    
private:
    std::string title;
    std::vector<T> items;
    DisplayFormatter displayFormatter;
    ItemSelectedCallback onItemSelected;
    Navigator& navigator;
    
    void showItems();
    bool processChoice(int choice);
};

// Implémentation dans le header car c'est un template

template<typename T>
ListWindow<T>::ListWindow(
    const std::string& title,
    const std::vector<T>& items,
    DisplayFormatter formatter,
    ItemSelectedCallback callback,
    Navigator& navigator
) : title(title), 
    items(items), 
    displayFormatter(formatter),
    onItemSelected(callback),
    navigator(navigator) {}

template<typename T>
void ListWindow<T>::show() {
    showItems();
    std::cout << "0. Retour" << std::endl;
    std::cout << "\nVotre choix : ";
}

template<typename T>
bool ListWindow<T>::handleInput() {
    int choice;
    if (!(std::cin >> choice)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "\nEntrée invalide. Appuyez sur Entrée pour continuer...";
        std::cin.get();
        return true;
    }
    
    return processChoice(choice);
}

template<typename T>
std::string ListWindow<T>::getTitle() const {
    return title;
}

template<typename T>
void ListWindow<T>::showItems() {
    for (size_t i = 0; i < items.size(); ++i) {
        std::cout << (i + 1) << ". " << displayFormatter(items[i]) << std::endl;
    }
}

template<typename T>
bool ListWindow<T>::processChoice(int choice) {
    if (choice == 0) {
        return false; // Retour
    }
    
    if (choice > 0 && choice <= static_cast<int>(items.size())) {
        onItemSelected(items[choice - 1], navigator);
        return true;
    }
    
    std::cout << "\nChoix invalide. Appuyez sur Entrée pour continuer...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();
    return true;
}

#endif // LISTWINDOW_H
