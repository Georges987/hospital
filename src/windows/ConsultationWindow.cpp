#include "ConsultationWindow.h"
#include "Navigator.h"
#include "Consultation.h"
#include "ConsultationStatus.h"
#include "HealthProfessional.h"
#include "ProfessionalType.h"
#include <iostream>
#include <limits>

ConsultationWindow::ConsultationWindow(const Patient& p, Navigator& nav)
    : patient(p), navigator(nav) {}

void ConsultationWindow::show() {
    showConsultations();
    std::cout << std::endl;
    showOptions();
}

bool ConsultationWindow::handleInput() {
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
            bookConsultation();
            break;
        case 2:
            completeConsultation();
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

std::string ConsultationWindow::getTitle() const {
    return "Consultations - " + patient.getFullName();
}

void ConsultationWindow::showConsultations() {
    auto consultations = Consultation::findByPatient(patient.getId());
    
    if (consultations.empty()) {
        std::cout << "⚠️  Aucune consultation enregistrée." << std::endl;
        return;
    }
    
    std::cout << "Historique des consultations :\n" << std::endl;
    
    for (const auto& consult : consultations) {
        std::string statusStr = consultationStatusToString(consult.getStatus());
        auto doctor = consult.getDoctor();
        
        std::cout << "[" << statusStr << "] " << consult.getDate() << " à " << consult.getTime() << std::endl;
        
        if (doctor) {
            std::cout << "  Médecin: " << doctor->getFullName();
            if (!doctor->getSpecialite().empty()) {
                std::cout << " (" << doctor->getSpecialite() << ")";
            }
            std::cout << std::endl;
        }
        
        if (!consult.getMotif().empty()) {
            std::cout << "  Motif: " << consult.getMotif() << std::endl;
        }
        
        if (!consult.getDiagnosis().empty()) {
            std::cout << "  Diagnostic: " << consult.getDiagnosis() << std::endl;
        }
        
        std::cout << std::endl;
    }
}

void ConsultationWindow::showOptions() {
    std::cout << "1. Programmer une consultation" << std::endl;
    std::cout << "2. Compléter une consultation" << std::endl;
    std::cout << "0. Retour" << std::endl;
    std::cout << "\nVotre choix : ";
}

void ConsultationWindow::bookConsultation() {
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    
    std::cout << "\n=== Programmer une consultation ===\n" << std::endl;
    
    // Sélection du médecin
    auto allProfessionals = HealthProfessional::all();
    std::vector<HealthProfessional> doctors;
    
    for (const auto& prof : allProfessionals) {
        if (prof.getType() == ProfessionalType::DOCTOR && prof.getIsActive()) {
            doctors.push_back(prof);
        }
    }
    
    if (doctors.empty()) {
        std::cout << "⚠️  Aucun médecin disponible." << std::endl;
        std::cout << "Appuyez sur Entrée pour continuer...";
        std::cin.get();
        return;
    }
    
    std::cout << "Médecins disponibles :\n" << std::endl;
    for (size_t i = 0; i < doctors.size(); ++i) {
        std::cout << (i + 1) << ". " << doctors[i].getFullName();
        if (!doctors[i].getSpecialite().empty()) {
            std::cout << " - " << doctors[i].getSpecialite();
        }
        std::cout << std::endl;
    }
    
    std::cout << "\nChoisissez un médecin (numéro) : ";
    int doctorChoice;
    std::cin >> doctorChoice;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    
    if (doctorChoice < 1 || doctorChoice > static_cast<int>(doctors.size())) {
        std::cout << "\nChoix invalide." << std::endl;
        std::cout << "Appuyez sur Entrée pour continuer...";
        std::cin.get();
        return;
    }
    
    auto& selectedDoctor = doctors[doctorChoice - 1];
    
    // Date
    std::cout << "\nDate (YYYY-MM-DD) : ";
    std::string date;
    std::getline(std::cin, date);
    
    if (date.empty()) {
        std::cout << "\nRéservation annulée." << std::endl;
        std::cout << "Appuyez sur Entrée pour continuer...";
        std::cin.get();
        return;
    }
    
    // Heure
    std::cout << "Heure (HH:MM) : ";
    std::string time;
    std::getline(std::cin, time);
    
    if (time.empty()) {
        std::cout << "\nRéservation annulée." << std::endl;
        std::cout << "Appuyez sur Entrée pour continuer...";
        std::cin.get();
        return;
    }
    
    // Motif
    std::cout << "Motif de consultation : ";
    std::string motif;
    std::getline(std::cin, motif);
    
    // Créer la consultation
    Consultation consultation(patient.getId(), selectedDoctor.getId(), date, time, motif);
    
    if (consultation.save()) {
        std::cout << "\n✅ Consultation programmée avec succès !" << std::endl;
        std::cout << "Date: " << date << " à " << time << std::endl;
        std::cout << "Médecin: " << selectedDoctor.getFullName() << std::endl;
    } else {
        std::cout << "\n❌ Erreur lors de la programmation." << std::endl;
    }
    
    std::cout << "\nAppuyez sur Entrée pour continuer...";
    std::cin.get();
}

void ConsultationWindow::completeConsultation() {
    auto consultations = Consultation::findByPatient(patient.getId());
    
    // Filtrer les consultations programmées
    std::vector<Consultation> scheduled;
    for (auto& c : consultations) {
        if (c.getStatus() == ConsultationStatus::SCHEDULED) {
            scheduled.push_back(c);
        }
    }
    
    if (scheduled.empty()) {
        std::cout << "\n⚠️  Aucune consultation programmée à compléter." << std::endl;
        std::cout << "Appuyez sur Entrée pour continuer...";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cin.get();
        return;
    }
    
    std::cout << "\nConsultations programmées :\n" << std::endl;
    for (size_t i = 0; i < scheduled.size(); ++i) {
        auto doctor = scheduled[i].getDoctor();
        std::cout << (i + 1) << ". " << scheduled[i].getDate() << " à " << scheduled[i].getTime();
        if (doctor) {
            std::cout << " - Dr. " << doctor->getFullName();
        }
        std::cout << std::endl;
    }
    
    std::cout << "\nChoisissez une consultation (numéro) : ";
    int choice;
    std::cin >> choice;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    
    if (choice < 1 || choice > static_cast<int>(scheduled.size())) {
        std::cout << "\nChoix invalide." << std::endl;
        std::cout << "Appuyez sur Entrée pour continuer...";
        std::cin.get();
        return;
    }
    
    auto& consultation = scheduled[choice - 1];
    
    // Observations
    std::cout << "\nObservations : ";
    std::string observations;
    std::getline(std::cin, observations);
    if (!observations.empty()) consultation.setObservations(observations);
    
    // Diagnostic
    std::cout << "Diagnostic : ";
    std::string diagnosis;
    std::getline(std::cin, diagnosis);
    if (!diagnosis.empty()) consultation.setDiagnosis(diagnosis);
    
    consultation.setStatus(ConsultationStatus::COMPLETED);
    
    if (consultation.save()) {
        std::cout << "\n✅ Consultation complétée avec succès !" << std::endl;
    } else {
        std::cout << "\n❌ Erreur lors de la mise à jour." << std::endl;
    }
    
    std::cout << "Appuyez sur Entrée pour continuer...";
    std::cin.get();
}
