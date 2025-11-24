#ifndef REFRESHABLELISTWINDOW_H
#define REFRESHABLELISTWINDOW_H

#include "Window.h"
#include "Navigator.h"
#include <vector>
#include <functional>
#include <string>
#include <iostream>
#include <limits>

template<typename T>
class RefreshableListWindow : public Window {
public:
    using DisplayFormatter = std::function<std::string(const T&)>;
    using ItemSelectedCallback = std::function<void(const T&, Navigator&)>;
    using DataLoader = std::function<std::vector<T>()>;
    
    RefreshableListWindow(
        const std::string& title,
        DataLoader loader,
        DisplayFormatter formatter,
        ItemSelectedCallback callback,
        Navigator& navigator
    );
    
    void show() override;
    bool handleInput() override;
    std::string getTitle() const override;
    
private:
    std::string title;
    DataLoader dataLoader;
    std::vector<T> items;
    DisplayFormatter displayFormatter;
    ItemSelectedCallback onItemSelected;
    Navigator& navigator;
    
    void refreshData();
    void showItems();
    bool processChoice(int choice);
};

// Implémentation dans le header car c'est un template

template<typename T>
RefreshableListWindow<T>::RefreshableListWindow(
    const std::string& title,
    DataLoader loader,
    DisplayFormatter formatter,
    ItemSelectedCallback callback,
    Navigator& navigator
) : title(title), 
    dataLoader(loader),
    displayFormatter(formatter),
    onItemSelected(callback),
    navigator(navigator) {
    refreshData();
}

template<typename T>
void RefreshableListWindow<T>::refreshData() {
    items = dataLoader();
}

template<typename T>
void RefreshableListWindow<T>::show() {
    // Rafraîchir les données à chaque affichage
    refreshData();
    
    if (items.empty()) {
        std::cout << "Aucun élément à afficher." << std::endl;
        std::cout << "\n0. Retour" << std::endl;
    } else {
        showItems();
        std::cout << "0. Retour" << std::endl;
    }
    std::cout << "\nVotre choix : ";
}

template<typename T>
bool RefreshableListWindow<T>::handleInput() {
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
std::string RefreshableListWindow<T>::getTitle() const {
    return title;
}

template<typename T>
void RefreshableListWindow<T>::showItems() {
    for (size_t i = 0; i < items.size(); ++i) {
        std::cout << (i + 1) << ". " << displayFormatter(items[i]) << std::endl;
    }
}

template<typename T>
bool RefreshableListWindow<T>::processChoice(int choice) {
    if (choice == 0) {
        return false; // Retour
    }
    
    if (choice > 0 && choice <= static_cast<int>(items.size())) {
        onItemSelected(items[choice - 1], navigator);
        // Après le retour de la fenêtre de détails, on reste dans la liste
        // qui sera automatiquement rafraîchie au prochain show()
        return true;
    }
    
    std::cout << "\nChoix invalide. Appuyez sur Entrée pour continuer...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();
    return true;
}

#endif // REFRESHABLELISTWINDOW_H
