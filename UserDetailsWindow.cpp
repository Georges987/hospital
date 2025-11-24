#include "UserDetailsWindow.h"
#include "Navigator.h"
#include "HealthProfessional.h"
#include "ProfessionalType.h"
#include <iostream>
#include <limits>

UserDetailsWindow::UserDetailsWindow(const User& u, Navigator& nav)
    : user(u), navigator(nav) {}

void UserDetailsWindow::show() {
    showDetails();
    std::cout << std::endl;
    showOptions();
}

bool UserDetailsWindow::handleInput() {
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
            // Changer le mot de passe
            std::cout << "\nNouveau mot de passe : ";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::string newPassword;
            std::getline(std::cin, newPassword);
            
            if (!newPassword.empty()) {
                user.setPassword(newPassword);
                if (user.save()) {
                    std::cout << "✅ Mot de passe modifié avec succès !" << std::endl;
                } else {
                    std::cout << "❌ Erreur lors de la modification." << std::endl;
                }
            }
            
            std::cout << "\nAppuyez sur Entrée pour continuer...";
            std::cin.get();
            break;
        }
        case 2: {
            // Supprimer l'utilisateur
            std::cout << "\nÊtes-vous sûr de vouloir supprimer cet utilisateur ? (1=Oui, 0=Non) : ";
            int confirm;
            std::cin >> confirm;
            
            if (confirm == 1) {
                if (user.remove()) {
                    std::cout << "✅ Utilisateur supprimé avec succès !" << std::endl;
                    std::cout << "\nAppuyez sur Entrée pour continuer...";
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cin.get();
                    return false; // Retour
                } else {
                    std::cout << "❌ Erreur lors de la suppression." << std::endl;
                }
            }
            
            std::cout << "\nAppuyez sur Entrée pour continuer...";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cin.get();
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

std::string UserDetailsWindow::getTitle() const {
    return "Détails Utilisateur - " + user.getUsername();
}

void UserDetailsWindow::showDetails() {
    std::cout << "Username   : " << user.getUsername() << std::endl;
    std::cout << "ID         : " << user.getId() << std::endl;
    
    auto professional = user.getHealthProfessional();
    if (professional) {
        std::cout << "\nProfessionnel associé :" << std::endl;
        std::cout << "Nom        : " << professional->getFullName() << std::endl;
        std::cout << "Email      : " << professional->getEmail() << std::endl;
        std::cout << "Type       : " << professionalTypeToString(professional->getType()) << std::endl;
        std::cout << "Téléphone  : " << professional->getTelephone() << std::endl;
    } else {
        std::cout << "\n⚠️  Professionnel non trouvé" << std::endl;
    }
}

void UserDetailsWindow::showOptions() {
    std::cout << "1. Changer le mot de passe" << std::endl;
    std::cout << "2. Supprimer l'utilisateur" << std::endl;
    std::cout << "0. Retour" << std::endl;
    std::cout << "\nVotre choix : ";
}
