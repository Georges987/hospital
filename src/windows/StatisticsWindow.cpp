#include "StatisticsWindow.h"
#include "Navigator.h"
#include "Statistics.h"
#include "ProfessionalType.h"
#include <iostream>
#include <limits>
#include <iomanip>

StatisticsWindow::StatisticsWindow(Navigator& nav) : navigator(nav) {}

void StatisticsWindow::show() {
    showDashboard();
}

bool StatisticsWindow::handleInput() {
    std::cout << "\nAppuyez sur Entrée pour revenir au menu...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();
    return false; // Retour
}

std::string StatisticsWindow::getTitle() const {
    return "Tableau de Bord - Statistiques";
}

void StatisticsWindow::showDashboard() {
    std::cout << "╔════════════════════════════════════════════════════╗" << std::endl;
    std::cout << "║          TABLEAU DE BORD DU SYSTÈME                ║" << std::endl;
    std::cout << "╚════════════════════════════════════════════════════╝" << std::endl;
    std::cout << std::endl;
    
    showPatientStats();
    std::cout << std::endl;
    
    showProfessionalStats();
    std::cout << std::endl;
    
    showMedicalDataStats();
}

void StatisticsWindow::showPatientStats() {
    std::cout << "📊 PATIENTS" << std::endl;
    std::cout << "─────────────────────────────────────────────────────" << std::endl;
    
    int total = Statistics::getTotalPatients();
    int males = Statistics::getPatientsBySex("M");
    int females = Statistics::getPatientsBySex("F");
    
    std::cout << "Total de patients       : " << total << std::endl;
    std::cout << "  • Hommes              : " << males << std::endl;
    std::cout << "  • Femmes              : " << females << std::endl;
    
    // Répartition par âge
    std::cout << "\nRépartition par âge :" << std::endl;
    std::cout << "  • 0-18 ans            : " << Statistics::getPatientsByAgeRange(0, 18) << std::endl;
    std::cout << "  • 19-40 ans           : " << Statistics::getPatientsByAgeRange(19, 40) << std::endl;
    std::cout << "  • 41-65 ans           : " << Statistics::getPatientsByAgeRange(41, 65) << std::endl;
    std::cout << "  • 65+ ans             : " << Statistics::getPatientsByAgeRange(66, 150) << std::endl;
}

void StatisticsWindow::showProfessionalStats() {
    std::cout << "👥 PROFESSIONNELS DE SANTÉ" << std::endl;
    std::cout << "─────────────────────────────────────────────────────" << std::endl;
    
    int total = Statistics::getTotalProfessionals();
    int active = Statistics::getActiveProfessionals();
    auto byType = Statistics::getProfessionalsByType();
    
    std::cout << "Total de professionnels : " << total << std::endl;
    std::cout << "  • Actifs              : " << active << std::endl;
    std::cout << "  • Inactifs            : " << (total - active) << std::endl;
    
    std::cout << "\nPar catégorie :" << std::endl;
    std::cout << "  • Administrateurs     : " << byType[ProfessionalType::ADMIN] << std::endl;
    std::cout << "  • Médecins            : " << byType[ProfessionalType::DOCTOR] << std::endl;
    std::cout << "  • Secrétaires         : " << byType[ProfessionalType::SECRETARY] << std::endl;
    
    int totalUsers = Statistics::getTotalUsers();
    int activeUsers = Statistics::getActiveUsers();
    std::cout << "\nComptes utilisateurs :" << std::endl;
    std::cout << "  • Total               : " << totalUsers << std::endl;
    std::cout << "  • Actifs              : " << activeUsers << std::endl;
}

void StatisticsWindow::showMedicalDataStats() {
    std::cout << "🏥 DONNÉES MÉDICALES" << std::endl;
    std::cout << "─────────────────────────────────────────────────────" << std::endl;
    
    int totalRecords = Statistics::getTotalMedicalRecords();
    int recordsWithDoctor = Statistics::getRecordsWithDoctor();
    
    std::cout << "Dossiers médicaux :" << std::endl;
    std::cout << "  • Total               : " << totalRecords << std::endl;
    std::cout << "  • Avec médecin        : " << recordsWithDoctor << std::endl;
    std::cout << "  • Sans médecin        : " << (totalRecords - recordsWithDoctor) << std::endl;
    
    int totalAnt = Statistics::getTotalAntecedents();
    int activeAnt = Statistics::getActiveAntecedents();
    auto antByType = Statistics::getAntecedentsByType();
    
    std::cout << "\nAntécédents médicaux :" << std::endl;
    std::cout << "  • Total               : " << totalAnt << std::endl;
    std::cout << "  • Actifs              : " << activeAnt << std::endl;
    
    if (totalAnt > 0) {
        std::cout << "\nPar type :" << std::endl;
        for (const auto& pair : antByType) {
            if (pair.second > 0) {
                std::cout << "  • " << std::setw(18) << std::left << pair.first 
                         << ": " << pair.second << std::endl;
            }
        }
    }
    
    // Consultations
    int totalConsult = Statistics::getTotalConsultations();
    int scheduledConsult = Statistics::getScheduledConsultations();
    int completedConsult = Statistics::getCompletedConsultations();
    
    std::cout << "\nConsultations :" << std::endl;
    std::cout << "  • Total               : " << totalConsult << std::endl;
    std::cout << "  • Programmées         : " << scheduledConsult << std::endl;
    std::cout << "  • Terminées           : " << completedConsult << std::endl;
    
    // Consultations par période (exemple: ce mois)
    std::time_t now = std::time(nullptr);
    std::tm* currentDate = std::localtime(&now);
    char startBuf[11], endBuf[11];
    
    // Premier jour du mois
    std::tm firstDay = *currentDate;
    firstDay.tm_mday = 1;
    std::strftime(startBuf, sizeof(startBuf), "%Y-%m-%d", &firstDay);
    
    // Dernier jour du mois
    std::tm lastDay = *currentDate;
    lastDay.tm_mon++;
    lastDay.tm_mday = 0;
    std::strftime(endBuf, sizeof(endBuf), "%Y-%m-%d", &lastDay);
    
    int thisMonth = Statistics::getConsultationsByDateRange(std::string(startBuf), std::string(endBuf));
    std::cout << "  • Ce mois             : " << thisMonth << std::endl;
}
