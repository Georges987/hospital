#include "MainWindow.h"
#include "Navigator.h"
#include "RefreshableListWindow.h"
#include "Patient.h"
#include "PatientDetailsWindow.h"
#include "PatientCreateWindow.h"
#include "UserManagementWindow.h"
#include "AuthService.h"
#include <iostream>
#include <limits>

MainWindow::MainWindow(Navigator& nav) : navigator(nav) {}

void MainWindow::show() {
    showOptions();
}

bool MainWindow::handleInput() {
    int choice;
    if (!(std::cin >> choice)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "\nEntrée invalide. Appuyez sur Entrée pour continuer...";
        std::cin.get();
        return true;
    }

    AuthService& auth = AuthService::getInstance();

    switch (choice) {
        case 1: {
            // Gestion des Patients
            showPatientsMenu();
            break;
        }
        case 2: {
            // Gestion des Utilisateurs (Admin uniquement)
            if (auth.hasPermission(ProfessionalType::ADMIN)) {
                showUsersMenu();
            } else {
                std::cout << "\n❌ Accès refusé. Réservé aux administrateurs." << std::endl;
                std::cout << "Appuyez sur Entrée pour continuer...";
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cin.get();
            }
            break;
        }
        case 3: {
            // Déconnexion
            std::cout << "\nDéconnexion..." << std::endl;
            auth.logout();
            return false; // Retour au LoginWindow
        }
        default:
            std::cout << "\nChoix invalide. Appuyez sur Entrée pour continuer...";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cin.get();
            break;
    }
    
    return true;
}

std::string MainWindow::getTitle() const {
    AuthService& auth = AuthService::getInstance();
    return "Menu Principal - " + auth.getCurrentProfessional()->getFullName();
}

void MainWindow::showOptions() {
    AuthService& auth = AuthService::getInstance();
    
    std::cout << "Connecté en tant que: " << auth.getCurrentProfessional()->getFullName() << std::endl;
    std::cout << "Rôle: " << professionalTypeToString(auth.getCurrentType()) << std::endl;
    std::cout << std::endl;
    
    std::cout << "1. Gestion des Patients" << std::endl;
    
    if (auth.hasPermission(ProfessionalType::ADMIN)) {
        std::cout << "2. Gestion des Utilisateurs" << std::endl;
    }
    
    std::cout << "3. Déconnexion" << std::endl;
    std::cout << "\nVotre choix : ";
}

void MainWindow::showPatientsMenu() {
    // Sous-menu pour les patients
    std::cout << "\n=== Gestion des Patients ===" << std::endl;
    std::cout << "1. Créer un patient" << std::endl;
    std::cout << "2. Liste des patients" << std::endl;
    std::cout << "0. Retour" << std::endl;
    std::cout << "\nVotre choix : ";
    
    int choice;
    std::cin >> choice;
    
    switch (choice) {
        case 1:
            navigator.push(std::make_unique<PatientCreateWindow>(navigator));
            break;
        case 2: {
            auto loader = []() { return Patient::all(); };
            auto formatter = [](const Patient& p) { 
                return p.getFullName() + " (" + std::to_string(p.getAge()) + " ans)"; 
            };
            auto callback = [](const Patient& p, Navigator& nav) {
                nav.push(std::make_unique<PatientDetailsWindow>(p, nav));
            };
            
            navigator.push(std::make_unique<RefreshableListWindow<Patient>>(
                "Liste des Patients",
                loader,
                formatter,
                callback,
                navigator
            ));
            break;
        }
        case 0:
            // Retour
            break;
        default:
            std::cout << "\nChoix invalide." << std::endl;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cin.get();
            break;
    }
}

void MainWindow::showUsersMenu() {
    navigator.push(std::make_unique<UserManagementWindow>(navigator));
}
