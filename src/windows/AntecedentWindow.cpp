#include "AntecedentWindow.h"
#include "Navigator.h"
#include "Antecedent.h"
#include "AntecedentType.h"
#include <iostream>
#include <limits>

AntecedentWindow::AntecedentWindow(const Patient& p, Navigator& nav)
    : patient(p), navigator(nav) {}

void AntecedentWindow::show() {
    showAntecedents();
    std::cout << std::endl;
    showOptions();
}

bool AntecedentWindow::handleInput() {
    int choice;
    if (!(std::cin >> choice)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "\nEntrée invalide. Appuyez sur Entrée pour continuer...";
        std::cin.get();
        return true;
    }
    
    switch (choice) {
        case 1:
            addAntecedent();
            break;
        case 2:
            toggleAntecedent();
            break;
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

std::string AntecedentWindow::getTitle() const {
    return "Antécédents - " + patient.getFullName();
}

void AntecedentWindow::showAntecedents() {
    auto antecedents = Antecedent::findByPatient(patient.getId());
    
    if (antecedents.empty()) {
        std::cout << "⚠️  Aucun antécédent médical enregistré." << std::endl;
        return;
    }
    
    std::cout << "Liste des antécédents médicaux :\n" << std::endl;
    
    for (const auto& ant : antecedents) {
        std::string status = ant.getIsActive() ? "✓" : "✗";
        std::string typeStr = antecedentTypeToString(ant.getType());
        std::string severityStr = severityToString(ant.getSeverity());
        
        std::cout << "[" << status << "] ID " << ant.getId() 
                  << " - " << typeStr 
                  << " (" << severityStr << ")" << std::endl;
        std::cout << "    " << ant.getDescription();
        
        if (!ant.getDate().empty()) {
            std::cout << " - " << ant.getDate();
        }
        
        std::cout << std::endl;
    }
}

void AntecedentWindow::showOptions() {
    std::cout << "1. Ajouter un antécédent" << std::endl;
    std::cout << "2. Activer/Désactiver un antécédent" << std::endl;
    std::cout << "0. Retour" << std::endl;
    std::cout << "\nVotre choix : ";
}

void AntecedentWindow::addAntecedent() {
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    
    std::cout << "\n=== Ajouter un antécédent ===\n" << std::endl;
    
    // Type
    std::cout << "Type d'antécédent :" << std::endl;
    std::cout << "0. Pathologie" << std::endl;
    std::cout << "1. Chirurgie" << std::endl;
    std::cout << "2. Allergie" << std::endl;
    std::cout << "3. Traitement antérieur" << std::endl;
    std::cout << "Choix : ";
    
    int typeChoice;
    std::cin >> typeChoice;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    
    if (typeChoice < 0 || typeChoice > 3) {
        std::cout << "\nType invalide." << std::endl;
        std::cout << "Appuyez sur Entrée pour continuer...";
        std::cin.get();
        return;
    }
    
    AntecedentType type = stringToAntecedentType(typeChoice);
    
    // Description
    std::cout << "\nDescription : ";
    std::string description;
    std::getline(std::cin, description);
    
    if (description.empty()) {
        std::cout << "\nAjout annulé." << std::endl;
        std::cout << "Appuyez sur Entrée pour continuer...";
        std::cin.get();
        return;
    }
    
    // Date (optionnelle)
    std::cout << "Date (YYYY-MM-DD, optionnel) : ";
    std::string date;
    std::getline(std::cin, date);
    
    // Sévérité
    std::cout << "\nSévérité :" << std::endl;
    std::cout << "0. Faible" << std::endl;
    std::cout << "1. Moyenne" << std::endl;
    std::cout << "2. Élevée" << std::endl;
    std::cout << "Choix : ";
    
    int severityChoice;
    std::cin >> severityChoice;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    
    if (severityChoice < 0 || severityChoice > 2) {
        severityChoice = 1; // Moyenne par défaut
    }
    
    Severity severity = stringToSeverity(severityChoice);
    
    // Créer l'antécédent
    Antecedent antecedent(patient.getId(), type, description, date, severity);
    
    if (antecedent.save()) {
        std::cout << "\n✅ Antécédent ajouté avec succès !" << std::endl;
    } else {
        std::cout << "\n❌ Erreur lors de l'ajout." << std::endl;
    }
    
    std::cout << "\nAppuyez sur Entrée pour continuer...";
    std::cin.get();
}

void AntecedentWindow::toggleAntecedent() {
    std::cout << "\nID de l'antécédent à activer/désactiver : ";
    int id;
    std::cin >> id;
    
    auto antecedent = Antecedent::find(id);
    if (!antecedent) {
        std::cout << "\n❌ Antécédent non trouvé." << std::endl;
        std::cout << "Appuyez sur Entrée pour continuer...";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cin.get();
        return;
    }
    
    // Vérifier que l'antécédent appartient au patient
    if (antecedent->getPatientId() != patient.getId()) {
        std::cout << "\n❌ Cet antécédent n'appartient pas à ce patient." << std::endl;
        std::cout << "Appuyez sur Entrée pour continuer...";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cin.get();
        return;
    }
    
    antecedent->setIsActive(!antecedent->getIsActive());
    
    if (antecedent->save()) {
        std::string status = antecedent->getIsActive() ? "activé" : "désactivé";
        std::cout << "\n✅ Antécédent " << status << " avec succès !" << std::endl;
    } else {
        std::cout << "\n❌ Erreur lors de la modification." << std::endl;
    }
    
    std::cout << "Appuyez sur Entrée pour continuer...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();
}
