#include "MainWindow.h"
#include <iostream>
#include <limits>

MainWindow::MainWindow() : running(true) {}

void MainWindow::run() {
    std::cout << "Bienvenue dans l'application MainWindow" << std::endl;
    while (running) {
        showOptions();
        handleInput();
    }
}

void MainWindow::showOptions() {
    std::cout << "\n--- Menu Principal ---" << std::endl;
    std::cout << "1. Option A" << std::endl;
    std::cout << "2. Option B" << std::endl;
    std::cout << "3. Quitter" << std::endl;
    std::cout << "Votre choix : ";
}

void MainWindow::handleInput() {
    int choice;
    if (!(std::cin >> choice)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Entrée invalide. Veuillez entrer un nombre." << std::endl;
        return;
    }

    switch (choice) {
        case 1:
            std::cout << "Vous avez choisi l'Option A." << std::endl;
            break;
        case 2:
            std::cout << "Vous avez choisi l'Option B." << std::endl;
            break;
        case 3:
            std::cout << "Au revoir !" << std::endl;
            running = false;
            break;
        default:
            std::cout << "Choix invalide. Veuillez réessayer." << std::endl;
            break;
    }
}
