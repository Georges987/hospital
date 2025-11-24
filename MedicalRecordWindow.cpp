#include "MedicalRecordWindow.h"
#include "Navigator.h"
#include "MedicalRecord.h"
#include "HealthProfessional.h"
#include "ProfessionalType.h"
#include <iostream>
#include <limits>

MedicalRecordWindow::MedicalRecordWindow(const Patient& p, Navigator& nav)
    : patient(p), navigator(nav) {}

void MedicalRecordWindow::show() {
    showMedicalRecord();
    std::cout << std::endl;
    showOptions();
}

bool MedicalRecordWindow::handleInput() {
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
            createOrUpdateRecord();
            break;
        case 2:
            assignDoctor();
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

std::string MedicalRecordWindow::getTitle() const {
    return "Dossier Médical - " + patient.getFullName();
}

void MedicalRecordWindow::showMedicalRecord() {
    auto records = MedicalRecord::findByPatient(patient.getId());
    
    if (records.empty()) {
        std::cout << "⚠️  Aucun dossier médical pour ce patient." << std::endl;
        return;
    }
    
    // Afficher le dernier dossier (le plus récent)
    auto& record = records.back();
    
    std::cout << "Dossier médical #" << record.getId() << std::endl;
    std::cout << "─────────────────────────────────────" << std::endl;
    
    auto doctor = record.getDoctor();
    if (doctor) {
        std::cout << "Médecin traitant : " << doctor->getFullName() << std::endl;
        std::cout << "Spécialité       : " << doctor->getSpecialite() << std::endl;
    } else {
        std::cout << "Médecin traitant : Non assigné" << std::endl;
    }
    
    std::cout << "\nDiagnostic : " << (record.getDiagnosis().empty() ? "(vide)" : record.getDiagnosis()) << std::endl;
    std::cout << "Traitement : " << (record.getTreatment().empty() ? "(vide)" : record.getTreatment()) << std::endl;
    std::cout << "Notes      : " << (record.getNotes().empty() ? "(vide)" : record.getNotes()) << std::endl;
    std::cout << "\nCréé le    : " << record.getCreatedAt() << std::endl;
    std::cout << "Modifié le : " << record.getUpdatedAt() << std::endl;
}

void MedicalRecordWindow::showOptions() {
    std::cout << "1. Modifier le dossier médical" << std::endl;
    std::cout << "2. Assigner/Changer le médecin" << std::endl;
    std::cout << "0. Retour" << std::endl;
    std::cout << "\nVotre choix : ";
}

void MedicalRecordWindow::createOrUpdateRecord() {
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    
    auto records = MedicalRecord::findByPatient(patient.getId());
    MedicalRecord record;
    
    if (!records.empty()) {
        // Modifier le dossier existant
        record = records.back();
        std::cout << "\nModification du dossier médical\n" << std::endl;
    } else {
        // Créer un nouveau dossier
        std::cout << "\nCréation d'un nouveau dossier médical\n" << std::endl;
        std::cout << "Veuillez d'abord assigner un médecin." << std::endl;
        std::cout << "\nAppuyez sur Entrée pour continuer...";
        std::cin.get();
        return;
    }
    
    std::cout << "Diagnostic (actuel: " << record.getDiagnosis() << ") : ";
    std::string diagnosis;
    std::getline(std::cin, diagnosis);
    if (!diagnosis.empty()) record.setDiagnosis(diagnosis);
    
    std::cout << "Traitement (actuel: " << record.getTreatment() << ") : ";
    std::string treatment;
    std::getline(std::cin, treatment);
    if (!treatment.empty()) record.setTreatment(treatment);
    
    std::cout << "Notes (actuel: " << record.getNotes() << ") : ";
    std::string notes;
    std::getline(std::cin, notes);
    if (!notes.empty()) record.setNotes(notes);
    
    if (record.save()) {
        std::cout << "\n✅ Dossier médical mis à jour avec succès !" << std::endl;
    } else {
        std::cout << "\n❌ Erreur lors de la mise à jour." << std::endl;
    }
    
    std::cout << "\nAppuyez sur Entrée pour continuer...";
    std::cin.get();
}

void MedicalRecordWindow::assignDoctor() {
    // Récupérer tous les médecins
    auto allProfessionals = HealthProfessional::all();
    std::vector<HealthProfessional> doctors;
    
    for (const auto& prof : allProfessionals) {
        if (prof.getType() == ProfessionalType::DOCTOR) {
            doctors.push_back(prof);
        }
    }
    
    if (doctors.empty()) {
        std::cout << "\n⚠️  Aucun médecin disponible dans le système." << std::endl;
        std::cout << "Appuyez sur Entrée pour continuer...";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cin.get();
        return;
    }
    
    std::cout << "\nListe des médecins disponibles :\n" << std::endl;
    for (size_t i = 0; i < doctors.size(); ++i) {
        std::cout << (i + 1) << ". " << doctors[i].getFullName() 
                  << " - " << doctors[i].getSpecialite() << std::endl;
    }
    
    std::cout << "\nChoisissez un médecin (numéro) : ";
    int choice;
    std::cin >> choice;
    
    if (choice < 1 || choice > static_cast<int>(doctors.size())) {
        std::cout << "\nChoix invalide." << std::endl;
        std::cout << "Appuyez sur Entrée pour continuer...";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cin.get();
        return;
    }
    
    auto& selectedDoctor = doctors[choice - 1];
    
    // Vérifier si un dossier existe
    auto records = MedicalRecord::findByPatient(patient.getId());
    
    if (records.empty()) {
        // Créer un nouveau dossier
        MedicalRecord newRecord(patient.getId(), selectedDoctor.getId());
        if (newRecord.save()) {
            std::cout << "\n✅ Dossier médical créé et médecin assigné !" << std::endl;
        } else {
            std::cout << "\n❌ Erreur lors de la création du dossier." << std::endl;
        }
    } else {
        // Mettre à jour le médecin du dossier existant
        auto& record = records.back();
        record.setDoctorId(selectedDoctor.getId());
        if (record.save()) {
            std::cout << "\n✅ Médecin assigné avec succès !" << std::endl;
        } else {
            std::cout << "\n❌ Erreur lors de l'assignation." << std::endl;
        }
    }
    
    std::cout << "Appuyez sur Entrée pour continuer...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();
}
