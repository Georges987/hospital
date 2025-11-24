#include "UserManagementWindow.h"
#include "Navigator.h"
#include "User.h"
#include "HealthProfessional.h"
#include "RefreshableListWindow.h"
#include "UserDetailsWindow.h"
#include "UserCreateWindow.h"
#include <iostream>
#include <limits>

UserManagementWindow::UserManagementWindow(Navigator& nav) : navigator(nav) {}

void UserManagementWindow::show() {
    showOptions();
}

bool UserManagementWindow::handleInput() {
    int choice;
    if (!(std::cin >> choice)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "\nEntrée invalide. Appuyez sur Entrée pour continuer...";
        std::cin.get();
        return true;
    }

    switch (choice) {
        case 1: {
            // Créer un utilisateur
            navigator.push(std::make_unique<UserCreateWindow>(navigator));
            break;
        }
        case 2: {
            // Liste des utilisateurs
            auto loader = []() { return User::all(); };
            
            auto formatter = [](const User& u) {
                auto prof = u.getHealthProfessional();
                if (prof) {
                    return u.getUsername() + " - " + prof->getFullName() + 
                           " (" + professionalTypeToString(prof->getType()) + ")";
                }
                return u.getUsername() + " - (Professionnel non trouvé)";
            };
            
            auto callback = [](const User& u, Navigator& nav) {
                nav.push(std::make_unique<UserDetailsWindow>(u, nav));
            };
            
            navigator.push(std::make_unique<RefreshableListWindow<User>>(
                "Liste des Utilisateurs",
                loader,
                formatter,
                callback,
                navigator
            ));
            break;
        }
        case 0:
            return false; // Retour
        default:
            std::cout << "\nChoix invalide. Appuyez sur Entrée pour continuer...";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cin.get();
            break;
    }
    
    return true;
}

std::string UserManagementWindow::getTitle() const {
    return "Gestion des Utilisateurs";
}

void UserManagementWindow::showOptions() {
    std::cout << "1. Créer un utilisateur" << std::endl;
    std::cout << "2. Liste des utilisateurs" << std::endl;
    std::cout << "0. Retour" << std::endl;
    std::cout << "\nVotre choix : ";
}
