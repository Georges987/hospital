#include "PatientDetailsWindow.h"
#include "Navigator.h"
#include "MedicalRecordWindow.h"
#include <iostream>
#include <limits>

PatientDetailsWindow::PatientDetailsWindow(const Patient& p, Navigator& nav)
    : patient(p), navigator(nav) {}

void PatientDetailsWindow::show() {
    showDetails();
    std::cout << std::endl;
    showOptions();
}

bool PatientDetailsWindow::handleInput() {
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
            // Modifier les informations
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            
            std::cout << "\nEmail (actuel: " << patient.getEmail() << ") : ";
            std::string email;
            std::getline(std::cin, email);
            if (!email.empty()) patient.setEmail(email);
            
            std::cout << "Adresse (actuel: " << patient.getAdresse() << ") : ";
            std::string adresse;
            std::getline(std::cin, adresse);
            if (!adresse.empty()) patient.setAdresse(adresse);
            
            if (patient.save()) {
                std::cout << "\n✅ Patient mis à jour avec succès !";
                
                // Recharger le patient depuis la DB pour synchroniser
                auto updatedPatient = Patient::find(patient.getId());
                if (updatedPatient) {
                    patient = *updatedPatient;
                }
            } else {
                std::cout << "\n❌ Erreur lors de la mise à jour.";
            }
            
            std::cout << "\nAppuyez sur Entrée pour continuer...";
            std::cin.get();
            break;
        }
        case 2: {
            // Dossier médical
            navigator.push(std::make_unique<MedicalRecordWindow>(patient, navigator));
            break;
        }
        case 3: {
            // Supprimer
            std::cout << "\nÊtes-vous sûr de vouloir supprimer ce patient ? (1=Oui, 0=Non) : ";
            int confirm;
            std::cin >> confirm;
            
            if (confirm == 1) {
                if (patient.remove()) {
                    std::cout << "Patient supprimé avec succès !";
                    std::cout << "\nAppuyez sur Entrée pour continuer...";
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cin.get();
                    return false; // Retour au menu précédent
                } else {
                    std::cout << "Erreur lors de la suppression.";
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

std::string PatientDetailsWindow::getTitle() const {
    return "Détails Patient - " + patient.getFullName();
}

void PatientDetailsWindow::showDetails() {
    std::cout << "ID              : " << patient.getId() << std::endl;
    std::cout << "Nom             : " << patient.getNom() << std::endl;
    std::cout << "Prénom          : " << patient.getPrenom() << std::endl;
    std::cout << "Date naissance  : " << patient.getDateNaissance() << std::endl;
    std::cout << "Âge             : " << patient.getAge() << " ans" << std::endl;
    std::cout << "Sexe            : " << patient.getSexe() << std::endl;
    std::cout << "Groupe sanguin  : " << (patient.getGroupeSanguin().empty() ? "(non renseigné)" : patient.getGroupeSanguin()) << std::endl;
    std::cout << "Téléphone       : " << patient.getTelephone() << std::endl;
    std::cout << "Email           : " << (patient.getEmail().empty() ? "(non renseigné)" : patient.getEmail()) << std::endl;
    std::cout << "Adresse         : " << (patient.getAdresse().empty() ? "(non renseignée)" : patient.getAdresse()) << std::endl;
}

void PatientDetailsWindow::showOptions() {
    std::cout << "1. Modifier les informations" << std::endl;
    std::cout << "2. Dossier médical" << std::endl;
    std::cout << "3. Supprimer le patient" << std::endl;
    std::cout << "0. Retour" << std::endl;
    std::cout << "\nVotre choix : ";
}
