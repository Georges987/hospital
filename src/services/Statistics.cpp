#include "Statistics.h"
#include "Database.h"
#include "Patient.h"
#include "HealthProfessional.h"
#include "User.h"
#include "Antecedent.h"
#include "MedicalRecord.h"
#include "AntecedentType.h"
#include <iostream>

// Patients
int Statistics::getTotalPatients() {
    auto patients = Patient::all();
    return patients.size();
}

int Statistics::getPatientsBySex(const std::string& sex) {
    Database& db = Database::getInstance();
    std::string sql = "SELECT COUNT(*) as count FROM patients WHERE sexe = '" + sex + "'";
    auto results = db.query(sql);
    
    if (!results.empty() && results[0].count("count")) {
        return std::stoi(results[0].at("count"));
    }
    return 0;
}

int Statistics::getPatientsByAgeRange(int minAge, int maxAge) {
    auto allPatients = Patient::all();
    int count = 0;
    
    for (const auto& patient : allPatients) {
        int age = patient.getAge();
        if (age >= minAge && age <= maxAge) {
            count++;
        }
    }
    
    return count;
}

// Professionnels
int Statistics::getTotalProfessionals() {
    auto professionals = HealthProfessional::all();
    return professionals.size();
}

std::map<ProfessionalType, int> Statistics::getProfessionalsByType() {
    std::map<ProfessionalType, int> result;
    result[ProfessionalType::ADMIN] = 0;
    result[ProfessionalType::DOCTOR] = 0;
    result[ProfessionalType::SECRETARY] = 0;
    
    auto professionals = HealthProfessional::all();
    for (const auto& prof : professionals) {
        result[prof.getType()]++;
    }
    
    return result;
}

int Statistics::getActiveProfessionals() {
    Database& db = Database::getInstance();
    std::string sql = "SELECT COUNT(*) as count FROM health_professionals WHERE is_active = 1";
    auto results = db.query(sql);
    
    if (!results.empty() && results[0].count("count")) {
        return std::stoi(results[0].at("count"));
    }
    return 0;
}

// Antécédents
int Statistics::getTotalAntecedents() {
    auto antecedents = Antecedent::all();
    return antecedents.size();
}

int Statistics::getActiveAntecedents() {
    Database& db = Database::getInstance();
    std::string sql = "SELECT COUNT(*) as count FROM antecedents WHERE is_active = 1";
    auto results = db.query(sql);
    
    if (!results.empty() && results[0].count("count")) {
        return std::stoi(results[0].at("count"));
    }
    return 0;
}

std::map<std::string, int> Statistics::getAntecedentsByType() {
    std::map<std::string, int> result;
    result["Pathologie"] = 0;
    result["Chirurgie"] = 0;
    result["Allergie"] = 0;
    result["Traitement"] = 0;
    
    auto antecedents = Antecedent::all();
    for (const auto& ant : antecedents) {
        std::string typeStr = antecedentTypeToString(ant.getType());
        result[typeStr]++;
    }
    
    return result;
}

// Dossiers médicaux
int Statistics::getTotalMedicalRecords() {
    auto records = MedicalRecord::all();
    return records.size();
}

int Statistics::getRecordsWithDoctor() {
    Database& db = Database::getInstance();
    std::string sql = "SELECT COUNT(*) as count FROM medical_records WHERE doctor_id IS NOT NULL AND doctor_id > 0";
    auto results = db.query(sql);
    
    if (!results.empty() && results[0].count("count")) {
        return std::stoi(results[0].at("count"));
    }
    return 0;
}

// Utilisateurs
int Statistics::getTotalUsers() {
    auto users = User::all();
    return users.size();
}

int Statistics::getActiveUsers() {
    Database& db = Database::getInstance();
    std::string sql = R"(
        SELECT COUNT(*) as count 
        FROM users u
        JOIN health_professionals hp ON u.health_professional_id = hp.id
        WHERE hp.is_active = 1
    )";
    auto results = db.query(sql);
    
    if (!results.empty() && results[0].count("count")) {
        return std::stoi(results[0].at("count"));
    }
    return 0;
}

// Consultations
int Statistics::getTotalConsultations() {
    Database& db = Database::getInstance();
    std::string sql = "SELECT COUNT(*) as count FROM consultations";
    auto results = db.query(sql);
    
    if (!results.empty() && results[0].count("count")) {
        return std::stoi(results[0].at("count"));
    }
    return 0;
}

int Statistics::getScheduledConsultations() {
    Database& db = Database::getInstance();
    std::string sql = "SELECT COUNT(*) as count FROM consultations WHERE status = 0";
    auto results = db.query(sql);
    
    if (!results.empty() && results[0].count("count")) {
        return std::stoi(results[0].at("count"));
    }
    return 0;
}

int Statistics::getCompletedConsultations() {
    Database& db = Database::getInstance();
    std::string sql = "SELECT COUNT(*) as count FROM consultations WHERE status = 1";
    auto results = db.query(sql);
    
    if (!results.empty() && results[0].count("count")) {
        return std::stoi(results[0].at("count"));
    }
    return 0;
}

int Statistics::getConsultationsByDateRange(const std::string& startDate, const std::string& endDate) {
    Database& db = Database::getInstance();
    std::string sql = "SELECT COUNT(*) as count FROM consultations WHERE date >= '" + startDate + 
                     "' AND date <= '" + endDate + "'";
    auto results = db.query(sql);
    
    if (!results.empty() && results[0].count("count")) {
        return std::stoi(results[0].at("count"));
    }
    return 0;
}

