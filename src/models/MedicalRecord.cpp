#include "MedicalRecord.h"
#include "Patient.h"
#include "HealthProfessional.h"
#include <iostream>
#include <ctime>

MedicalRecord::MedicalRecord(int patientId, int doctorId, const std::string& diagnosis,
                             const std::string& treatment, const std::string& notes)
    : patientId(patientId), doctorId(doctorId), diagnosis(diagnosis),
      treatment(treatment), notes(notes) {
    createdAt = getCurrentTimestamp();
    updatedAt = createdAt;
}

std::unique_ptr<Patient> MedicalRecord::getPatient() const {
    return Patient::find(patientId);
}

std::unique_ptr<HealthProfessional> MedicalRecord::getDoctor() const {
    return HealthProfessional::find(doctorId);
}

std::vector<MedicalRecord> MedicalRecord::findByPatient(int patientId) {
    Database& db = Database::getInstance();
    std::string sql = "SELECT * FROM medical_records WHERE patient_id = " + std::to_string(patientId);
    auto results = db.query(sql);
    
    std::vector<MedicalRecord> records;
    for (const auto& row : results) {
        MedicalRecord record;
        record.fromMap(row);
        records.push_back(record);
    }
    
    return records;
}

std::vector<MedicalRecord> MedicalRecord::findByDoctor(int doctorId) {
    Database& db = Database::getInstance();
    std::string sql = "SELECT * FROM medical_records WHERE doctor_id = " + std::to_string(doctorId);
    auto results = db.query(sql);
    
    std::vector<MedicalRecord> records;
    for (const auto& row : results) {
        MedicalRecord record;
        record.fromMap(row);
        records.push_back(record);
    }
    
    return records;
}

void MedicalRecord::createTable() {
    Database& db = Database::getInstance();
    
    std::string sql = R"(
        CREATE TABLE IF NOT EXISTS medical_records (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            patient_id INTEGER NOT NULL,
            doctor_id INTEGER NOT NULL,
            diagnosis TEXT,
            treatment TEXT,
            notes TEXT,
            created_at TEXT NOT NULL,
            updated_at TEXT NOT NULL,
            FOREIGN KEY (patient_id) REFERENCES patients(id),
            FOREIGN KEY (doctor_id) REFERENCES health_professionals(id)
        )
    )";
    
    if (db.execute(sql)) {
        std::cout << "Table 'medical_records' créée avec succès" << std::endl;
    } else {
        std::cerr << "Erreur création table 'medical_records': " << db.getLastError() << std::endl;
    }
}

std::string MedicalRecord::getTableName() const {
    return "medical_records";
}

std::map<std::string, std::string> MedicalRecord::toMap() const {
    // Mettre à jour le timestamp lors de la sauvegarde
    const_cast<MedicalRecord*>(this)->updatedAt = getCurrentTimestamp();
    
    return {
        {"id", std::to_string(id)},
        {"patient_id", std::to_string(patientId)},
        {"doctor_id", std::to_string(doctorId)},
        {"diagnosis", diagnosis},
        {"treatment", treatment},
        {"notes", notes},
        {"created_at", createdAt},
        {"updated_at", updatedAt}
    };
}

void MedicalRecord::fromMap(const std::map<std::string, std::string>& data) {
    if (data.count("id")) id = std::stoi(data.at("id"));
    if (data.count("patient_id")) patientId = std::stoi(data.at("patient_id"));
    if (data.count("doctor_id")) doctorId = std::stoi(data.at("doctor_id"));
    if (data.count("diagnosis")) diagnosis = data.at("diagnosis");
    if (data.count("treatment")) treatment = data.at("treatment");
    if (data.count("notes")) notes = data.at("notes");
    if (data.count("created_at")) createdAt = data.at("created_at");
    if (data.count("updated_at")) updatedAt = data.at("updated_at");
}

std::string MedicalRecord::getCurrentTimestamp() const {
    std::time_t now = std::time(nullptr);
    char buf[20];
    std::strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", std::localtime(&now));
    return std::string(buf);
}
