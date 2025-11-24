#include "UserCreateWindow.h"
#include "Navigator.h"
#include "User.h"
#include "HealthProfessional.h"
#include "ProfessionalType.h"
#include <iostream>
#include <limits>

UserCreateWindow::UserCreateWindow(Navigator& nav) : navigator(nav) {}

void UserCreateWindow::show() {
    std::cout << "Créer un nouvel utilisateur\n" << std::endl;
    std::cout << "Étape 1 : Créer le professionnel de santé\n" << std::endl;
}

bool UserCreateWindow::handleInput() {
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    
    // Informations du professionnel
    std::string nom = readString("Nom : ");
    if (nom.empty()) return false;
    
    std::string prenom = readString("Prénom : ");
    if (prenom.empty()) return false;
    
    std::string email = readString("Email : ");
    if (email.empty()) return false;
    
    std::string telephone = readString("Téléphone (optionnel) : ");
    
    // Choix du type
    std::cout << "\nType de professionnel :" << std::endl;
    std::cout << "0. Administrateur" << std::endl;
    std::cout << "1. Médecin" << std::endl;
    std::cout << "2. Secrétaire" << std::endl;
    int typeChoice = readInt("Votre choix : ");
    
    ProfessionalType type;
    switch (typeChoice) {
        case 0: type = ProfessionalType::ADMIN; break;
        case 1: type = ProfessionalType::DOCTOR; break;
        case 2: type = ProfessionalType::SECRETARY; break;
        default:
            std::cout << "\nType invalide." << std::endl;
            std::cout << "Appuyez sur Entrée pour continuer...";
            std::cin.get();
            return false;
    }
    
    // Créer le professionnel
    HealthProfessional professional(nom, prenom, email, type);
    professional.setTelephone(telephone);
    
    // Attributs spécifiques selon le type
    if (type == ProfessionalType::DOCTOR) {
        std::string specialite = readString("Spécialité : ");
        professional.setSpecialite(specialite);
        
        std::string numeroOrdre = readString("Numéro d'ordre : ");
        professional.setNumeroOrdre(numeroOrdre);
    } else if (type == ProfessionalType::SECRETARY) {
        std::string service = readString("Service : ");
        professional.setService(service);
    } else if (type == ProfessionalType::ADMIN) {
        std::string department = readString("Département : ");
        professional.setDepartment(department);
    }
    
    if (!professional.save()) {
        std::cout << "\n❌ Erreur lors de la création du professionnel." << std::endl;
        std::cout << "Appuyez sur Entrée pour continuer...";
        std::cin.get();
        return false;
    }
    
    std::cout << "\n✅ Professionnel créé avec ID: " << professional.getId() << std::endl;
    
    // Créer le compte utilisateur
    std::cout << "\nÉtape 2 : Créer le compte utilisateur\n" << std::endl;
    
    std::string username = readString("Nom d'utilisateur : ");
    if (username.empty()) return false;
    
    std::string password = readString("Mot de passe : ");
    if (password.empty()) return false;
    
    User user(professional.getId(), username, password);
    if (user.save()) {
        std::cout << "\n✅ Utilisateur créé avec succès !" << std::endl;
        std::cout << "Username: " << username << std::endl;
    } else {
        std::cout << "\n❌ Erreur lors de la création de l'utilisateur." << std::endl;
    }
    
    std::cout << "\nAppuyez sur Entrée pour continuer...";
    std::cin.get();
    
    return false; // Retour au menu
}

std::string UserCreateWindow::getTitle() const {
    return "Créer un Utilisateur";
}

std::string UserCreateWindow::readString(const std::string& prompt) {
    std::cout << prompt;
    std::string value;
    std::getline(std::cin, value);
    return value;
}

int UserCreateWindow::readInt(const std::string& prompt) {
    std::cout << prompt;
    int value;
    if (!(std::cin >> value)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return -1;
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return value;
}
