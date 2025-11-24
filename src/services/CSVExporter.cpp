#include "CSVExporter.h"
#include "Patient.h"
#include "Consultation.h"
#include "HealthProfessional.h"
#include "ConsultationStatus.h"
#include "Statistics.h"
#include "ProfessionalType.h"
#include <fstream>
#include <iostream>
#include <sstream>

std::string CSVExporter::escapeCSV(const std::string& value) {
    if (value.find(',') != std::string::npos || 
        value.find('"') != std::string::npos || 
        value.find('\n') != std::string::npos) {
        std::string escaped = "\"";
        for (char c : value) {
            if (c == '"') escaped += "\"\"";
            else escaped += c;
        }
        escaped += "\"";
        return escaped;
    }
    return value;
}

bool CSVExporter::writeToFile(const std::string& filename, const std::vector<std::string>& lines) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Erreur: impossible d'ouvrir " << filename << std::endl;
        return false;
    }
    
    for (const auto& line : lines) {
        file << line << "\n";
    }
    
    file.close();
    return true;
}

bool CSVExporter::exportPatients(const std::string& filename) {
    auto patients = Patient::all();
    
    std::vector<std::string> lines;
    
    // Header
    lines.push_back("ID,Nom,Prénom,Date Naissance,Âge,Sexe,Groupe Sanguin,Téléphone,Email,Adresse,Numéro Sécu");
    
    // Data
    for (const auto& patient : patients) {
        std::ostringstream oss;
        oss << patient.getId() << ","
            << escapeCSV(patient.getNom()) << ","
            << escapeCSV(patient.getPrenom()) << ","
            << escapeCSV(patient.getDateNaissance()) << ","
            << patient.getAge() << ","
            << escapeCSV(patient.getSexe()) << ","
            << escapeCSV(patient.getGroupeSanguin()) << ","
            << escapeCSV(patient.getTelephone()) << ","
            << escapeCSV(patient.getEmail()) << ","
            << escapeCSV(patient.getAdresse()) << ","
            << escapeCSV(patient.getNumeroSecu());
        
        lines.push_back(oss.str());
    }
    
    bool success = writeToFile(filename, lines);
    if (success) {
        std::cout << "✅ " << patients.size() << " patients exportés vers " << filename << std::endl;
    }
    return success;
}

bool CSVExporter::exportConsultations(const std::string& filename) {
    auto consultations = Consultation::all();
    
    std::vector<std::string> lines;
    
    // Header
    lines.push_back("ID,Patient,Médecin,Date,Heure,Motif,Diagnostic,Statut");
    
    // Data
    for (const auto& consult : consultations) {
        auto patient = consult.getPatient();
        auto doctor = consult.getDoctor();
        
        std::string patientName = patient ? patient->getFullName() : "Inconnu";
        std::string doctorName = doctor ? doctor->getFullName() : "Inconnu";
        
        std::ostringstream oss;
        oss << consult.getId() << ","
            << escapeCSV(patientName) << ","
            << escapeCSV(doctorName) << ","
            << escapeCSV(consult.getDate()) << ","
            << escapeCSV(consult.getTime()) << ","
            << escapeCSV(consult.getMotif()) << ","
            << escapeCSV(consult.getDiagnosis()) << ","
            << escapeCSV(consultationStatusToString(consult.getStatus()));
        
        lines.push_back(oss.str());
    }
    
    bool success = writeToFile(filename, lines);
    if (success) {
        std::cout << "✅ " << consultations.size() << " consultations exportées vers " << filename << std::endl;
    }
    return success;
}

bool CSVExporter::exportStatistics(const std::string& filename) {
    std::vector<std::string> lines;
    
    // Header
    lines.push_back("Catégorie,Métrique,Valeur");
    
    // Patients
    lines.push_back("Patients,Total," + std::to_string(Statistics::getTotalPatients()));
    lines.push_back("Patients,Hommes," + std::to_string(Statistics::getPatientsBySex("M")));
    lines.push_back("Patients,Femmes," + std::to_string(Statistics::getPatientsBySex("F")));
    
    // Professionnels
    lines.push_back("Professionnels,Total," + std::to_string(Statistics::getTotalProfessionals()));
    lines.push_back("Professionnels,Actifs," + std::to_string(Statistics::getActiveProfessionals()));
    
    auto byType = Statistics::getProfessionalsByType();
    lines.push_back("Professionnels,Administrateurs," + std::to_string(byType[ProfessionalType::ADMIN]));
    lines.push_back("Professionnels,Médecins," + std::to_string(byType[ProfessionalType::DOCTOR]));
    lines.push_back("Professionnels,Secrétaires," + std::to_string(byType[ProfessionalType::SECRETARY]));
    
    // Consultations
    lines.push_back("Consultations,Total," + std::to_string(Statistics::getTotalConsultations()));
    lines.push_back("Consultations,Programmées," + std::to_string(Statistics::getScheduledConsultations()));
    lines.push_back("Consultations,Terminées," + std::to_string(Statistics::getCompletedConsultations()));
    
    // Antécédents
    lines.push_back("Antécédents,Total," + std::to_string(Statistics::getTotalAntecedents()));
    lines.push_back("Antécédents,Actifs," + std::to_string(Statistics::getActiveAntecedents()));
    
    bool success = writeToFile(filename, lines);
    if (success) {
        std::cout << "✅ Statistiques exportées vers " << filename << std::endl;
    }
    return success;
}
