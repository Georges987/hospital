#include "ExportWindow.h"
#include "Navigator.h"
#include "CSVExporter.h"
#include <iostream>
#include <limits>

ExportWindow::ExportWindow(Navigator& nav) : navigator(nav) {}

void ExportWindow::show() {
    std::cout << "=== Export de Données (CSV) ===" << std::endl;
    std::cout << std::endl;
    showOptions();
}

bool ExportWindow::handleInput() {
    int choice;
    if (!(std::cin >> choice)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "\nEntrée invalide. Appuyez sur Entrée pour continuer...";
        std::cin.get();
        return true;
    }
    
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    
    switch (choice) {
        case 1: {
            // Export patients
            std::cout << "\nExport des patients..." << std::endl;
            CSVExporter::exportPatients("patients_export.csv");
            std::cout << "\nFichier créé: patients_export.csv" << std::endl;
            break;
        }
        case 2: {
            // Export consultations
            std::cout << "\nExport des consultations..." << std::endl;
            CSVExporter::exportConsultations("consultations_export.csv");
            std::cout << "\nFichier créé: consultations_export.csv" << std::endl;
            break;
        }
        case 3: {
            // Export statistics
            std::cout << "\nExport des statistiques..." << std::endl;
            CSVExporter::exportStatistics("statistiques_export.csv");
            std::cout << "\nFichier créé: statistiques_export.csv" << std::endl;
            break;
        }
        case 0:
            return false; // Retour
        default:
            std::cout << "\nChoix invalide." << std::endl;
            break;
    }
    
    std::cout << "\nAppuyez sur Entrée pour continuer...";
    std::cin.get();
    return true;
}

std::string ExportWindow::getTitle() const {
    return "Export CSV";
}

void ExportWindow::showOptions() {
    std::cout << "1. Exporter les patients" << std::endl;
    std::cout << "2. Exporter les consultations" << std::endl;
    std::cout << "3. Exporter les statistiques" << std::endl;
    std::cout << "0. Retour" << std::endl;
    std::cout << "\nVotre choix : ";
}
