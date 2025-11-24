#include "PatientCreateWindow.h"
#include "Navigator.h"
#include "Patient.h"
#include <iostream>
#include <limits>

PatientCreateWindow::PatientCreateWindow(Navigator& nav) : navigator(nav) {}

void PatientCreateWindow::show() {
    std::cout << "Créer un nouveau patient\n" << std::endl;
    std::cout << "Entrez les informations du patient :\n" << std::endl;
}

bool PatientCreateWindow::handleInput() {
    // Nettoyer le buffer d'entrée avant de lire
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    
    std::string nom = readString("Nom : ");
    if (nom.empty()) {
        std::cout << "\nCréation annulée." << std::endl;
        std::cout << "Appuyez sur Entrée pour continuer...";
        std::cin.get();
        return false;
    }
    
    std::string prenom = readString("Prénom : ");
    if (prenom.empty()) {
        std::cout << "\nCréation annulée." << std::endl;
        std::cout << "Appuyez sur Entrée pour continuer...";
        std::cin.get();
        return false;
    }
    
    int age = readInt("Âge : ");
    if (age < 0) {
        std::cout << "\nCréation annulée." << std::endl;
        std::cout << "Appuyez sur Entrée pour continuer...";
        std::cin.get();
        return false;
    }
    
    std::string telephone = readString("Téléphone (optionnel) : ");
    
    // Créer et sauvegarder le patient
    Patient patient(nom, prenom, age, telephone);
    if (patient.save()) {
        std::cout << "\n✅ Patient créé avec succès ! (ID: " << patient.getId() << ")" << std::endl;
    } else {
        std::cout << "\n❌ Erreur lors de la création du patient." << std::endl;
    }
    
    std::cout << "\nAppuyez sur Entrée pour continuer...";
    std::cin.get();
    
    return false; // Retour au menu
}

std::string PatientCreateWindow::getTitle() const {
    return "Créer un Patient";
}

std::string PatientCreateWindow::readString(const std::string& prompt) {
    std::cout << prompt;
    std::string value;
    std::getline(std::cin, value);
    return value;
}

int PatientCreateWindow::readInt(const std::string& prompt) {
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
