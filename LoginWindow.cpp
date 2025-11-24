#include "LoginWindow.h"
#include "Navigator.h"
#include "AuthService.h"
#include "MainWindow.h"
#include <iostream>
#include <limits>

LoginWindow::LoginWindow(Navigator& nav) : navigator(nav) {}

void LoginWindow::show() {
    std::cout << "╔════════════════════════════════════╗" << std::endl;
    std::cout << "║   SYSTÈME DE GESTION HOSPITALIÈRE  ║" << std::endl;
    std::cout << "╚════════════════════════════════════╝" << std::endl;
    std::cout << std::endl;
    std::cout << "Veuillez vous connecter\n" << std::endl;
}

bool LoginWindow::handleInput() {
    std::string username;
    
    // Boucle jusqu'à obtenir un username valide ou annulation explicite
    while (true) {
        username = readUsername();
        
        // Si l'utilisateur entre quelque chose, on continue
        if (!username.empty()) {
            break;
        }
        
        // Si vide, on redemande (au lieu de quitter)
        std::cout << "\nLe nom d'utilisateur ne peut pas être vide." << std::endl;
        std::cout << "Appuyez sur Entrée pour réessayer (ou Ctrl+C pour quitter)...";
        std::cin.get();
        clearScreen();
        show();
    }
    
    std::string password = readPassword();
    
    AuthService& auth = AuthService::getInstance();
    if (auth.login(username, password)) {
        std::cout << "\n✅ Connexion réussie !" << std::endl;
        std::cout << "Bienvenue " << auth.getCurrentProfessional()->getFullName() << std::endl;
        std::cout << "Rôle: " << professionalTypeToString(auth.getCurrentType()) << std::endl;
        std::cout << "\nAppuyez sur Entrée pour continuer...";
        std::cin.get();
        
        // Rediriger vers MainWindow
        navigator.push(std::make_unique<MainWindow>(navigator));
        return true; // Garder LoginWindow dans la pile (il sera masqué par MainWindow)
    } else {
        std::cout << "\n❌ Identifiants incorrects." << std::endl;
        std::cout << "\nAppuyez sur Entrée pour réessayer...";
        std::cin.get();
        return true; // Rester sur LoginWindow
    }
}

void LoginWindow::clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

std::string LoginWindow::getTitle() const {
    return "Connexion";
}

std::string LoginWindow::readUsername() {
    std::cout << "Nom d'utilisateur : ";
    std::string username;
    std::getline(std::cin, username);
    return username;
}

std::string LoginWindow::readPassword() {
    std::cout << "Mot de passe : ";
    std::string password;
    std::getline(std::cin, password);
    return password;
}
