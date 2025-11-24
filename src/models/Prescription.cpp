#include "Prescription.h"
#include "Consultation.h"
#include <iostream>
#include <ctime>

Prescription::Prescription(int consultationId, const std::string& medication,
                          const std::string& dosage, int durationDays)
    : consultationId(consultationId), medication(medication), 
      dosage(dosage), durationDays(durationDays) {
    createdAt = getCurrentTimestamp();
}

std::unique_ptr<Consultation> Prescription::getConsultation() const {
    return Consultation::find(consultationId);
}

std::vector<Prescription> Prescription::findByConsultation(int consultationId) {
    Database& db = Database::getInstance();
    std::string sql = "SELECT * FROM prescriptions WHERE consultation_id = " + std::to_string(consultationId);
    auto results = db.query(sql);
    
    std::vector<Prescription> prescriptions;
    for (const auto& row : results) {
        Prescription prescription;
        prescription.fromMap(row);
        prescriptions.push_back(prescription);
    }
    
    return prescriptions;
}

std::vector<Prescription> Prescription::findByPatient(int patientId) {
    Database& db = Database::getInstance();
    std::string sql = R"(
        SELECT p.* FROM prescriptions p
        JOIN consultations c ON p.consultation_id = c.id
        WHERE c.patient_id = )" + std::to_string(patientId) + 
        " ORDER BY p.created_at DESC";
    auto results = db.query(sql);
    
    std::vector<Prescription> prescriptions;
    for (const auto& row : results) {
        Prescription prescription;
        prescription.fromMap(row);
        prescriptions.push_back(prescription);
    }
    
    return prescriptions;
}

void Prescription::createTable() {
    Database& db = Database::getInstance();
    
    std::string sql = R"(
        CREATE TABLE IF NOT EXISTS prescriptions (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            consultation_id INTEGER NOT NULL,
            medication TEXT NOT NULL,
            dosage TEXT NOT NULL,
            duration_days INTEGER NOT NULL,
            instructions TEXT,
            created_at TEXT NOT NULL,
            FOREIGN KEY (consultation_id) REFERENCES consultations(id)
        )
    )";
    
    if (db.execute(sql)) {
        std::cout << "Table 'prescriptions' créée avec succès" << std::endl;
    } else {
        std::cerr << "Erreur création table 'prescriptions': " << db.getLastError() << std::endl;
    }
}

std::string Prescription::getTableName() const {
    return "prescriptions";
}

std::map<std::string, std::string> Prescription::toMap() const {
    return {
        {"id", std::to_string(id)},
        {"consultation_id", std::to_string(consultationId)},
        {"medication", medication},
        {"dosage", dosage},
        {"duration_days", std::to_string(durationDays)},
        {"instructions", instructions},
        {"created_at", createdAt}
    };
}

void Prescription::fromMap(const std::map<std::string, std::string>& data) {
    if (data.count("id")) id = std::stoi(data.at("id"));
    if (data.count("consultation_id")) consultationId = std::stoi(data.at("consultation_id"));
    if (data.count("medication")) medication = data.at("medication");
    if (data.count("dosage")) dosage = data.at("dosage");
    if (data.count("duration_days")) durationDays = std::stoi(data.at("duration_days"));
    if (data.count("instructions")) instructions = data.at("instructions");
    if (data.count("created_at")) createdAt = data.at("created_at");
}

std::string Prescription::getCurrentTimestamp() const {
    std::time_t now = std::time(nullptr);
    char buf[20];
    std::strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", std::localtime(&now));
    return std::string(buf);
}
