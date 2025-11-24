#include "Consultation.h"
#include "Patient.h"
#include "HealthProfessional.h"
#include <iostream>
#include <ctime>

Consultation::Consultation(int patientId, int doctorId, const std::string& date,
                          const std::string& time, const std::string& motif)
    : patientId(patientId), doctorId(doctorId), date(date), time(time), motif(motif) {
    createdAt = getCurrentTimestamp();
}

std::unique_ptr<Patient> Consultation::getPatient() const {
    return Patient::find(patientId);
}

std::unique_ptr<HealthProfessional> Consultation::getDoctor() const {
    return HealthProfessional::find(doctorId);
}

std::vector<Consultation> Consultation::findByPatient(int patientId) {
    Database& db = Database::getInstance();
    std::string sql = "SELECT * FROM consultations WHERE patient_id = " + std::to_string(patientId) +
                     " ORDER BY date DESC, time DESC";
    auto results = db.query(sql);
    
    std::vector<Consultation> consultations;
    for (const auto& row : results) {
        Consultation consultation;
        consultation.fromMap(row);
        consultations.push_back(consultation);
    }
    
    return consultations;
}

std::vector<Consultation> Consultation::findByDoctor(int doctorId) {
    Database& db = Database::getInstance();
    std::string sql = "SELECT * FROM consultations WHERE doctor_id = " + std::to_string(doctorId) +
                     " ORDER BY date DESC, time DESC";
    auto results = db.query(sql);
    
    std::vector<Consultation> consultations;
    for (const auto& row : results) {
        Consultation consultation;
        consultation.fromMap(row);
        consultations.push_back(consultation);
    }
    
    return consultations;
}

std::vector<Consultation> Consultation::findByDate(const std::string& date) {
    Database& db = Database::getInstance();
    std::string sql = "SELECT * FROM consultations WHERE date = '" + date + "' ORDER BY time";
    auto results = db.query(sql);
    
    std::vector<Consultation> consultations;
    for (const auto& row : results) {
        Consultation consultation;
        consultation.fromMap(row);
        consultations.push_back(consultation);
    }
    
    return consultations;
}

std::vector<Consultation> Consultation::findUpcoming() {
    Database& db = Database::getInstance();
    std::string sql = "SELECT * FROM consultations WHERE status = 0 AND date >= date('now') ORDER BY date, time";
    auto results = db.query(sql);
    
    std::vector<Consultation> consultations;
    for (const auto& row : results) {
        Consultation consultation;
        consultation.fromMap(row);
        consultations.push_back(consultation);
    }
    
    return consultations;
}

std::vector<Consultation> Consultation::findByDateRange(const std::string& startDate, const std::string& endDate) {
    Database& db = Database::getInstance();
    std::string sql = "SELECT * FROM consultations WHERE date >= '" + startDate + 
                     "' AND date <= '" + endDate + "' ORDER BY date, time";
    auto results = db.query(sql);
    
    std::vector<Consultation> consultations;
    for (const auto& row : results) {
        Consultation consultation;
        consultation.fromMap(row);
        consultations.push_back(consultation);
    }
    
    return consultations;
}

void Consultation::createTable() {
    Database& db = Database::getInstance();
    
    std::string sql = R"(
        CREATE TABLE IF NOT EXISTS consultations (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            patient_id INTEGER NOT NULL,
            doctor_id INTEGER NOT NULL,
            date TEXT NOT NULL,
            time TEXT NOT NULL,
            motif TEXT,
            observations TEXT,
            diagnosis TEXT,
            status INTEGER DEFAULT 0,
            duration INTEGER DEFAULT 30,
            created_at TEXT NOT NULL,
            FOREIGN KEY (patient_id) REFERENCES patients(id),
            FOREIGN KEY (doctor_id) REFERENCES health_professionals(id)
        )
    )";
    
    if (db.execute(sql)) {
        std::cout << "Table 'consultations' créée avec succès" << std::endl;
    } else {
        std::cerr << "Erreur création table 'consultations': " << db.getLastError() << std::endl;
    }
}

std::string Consultation::getTableName() const {
    return "consultations";
}

std::map<std::string, std::string> Consultation::toMap() const {
    return {
        {"id", std::to_string(id)},
        {"patient_id", std::to_string(patientId)},
        {"doctor_id", std::to_string(doctorId)},
        {"date", date},
        {"time", time},
        {"motif", motif},
        {"observations", observations},
        {"diagnosis", diagnosis},
        {"status", std::to_string(static_cast<int>(status))},
        {"duration", std::to_string(duration)},
        {"created_at", createdAt}
    };
}

void Consultation::fromMap(const std::map<std::string, std::string>& data) {
    if (data.count("id")) id = std::stoi(data.at("id"));
    if (data.count("patient_id")) patientId = std::stoi(data.at("patient_id"));
    if (data.count("doctor_id")) doctorId = std::stoi(data.at("doctor_id"));
    if (data.count("date")) date = data.at("date");
    if (data.count("time")) time = data.at("time");
    if (data.count("motif")) motif = data.at("motif");
    if (data.count("observations")) observations = data.at("observations");
    if (data.count("diagnosis")) diagnosis = data.at("diagnosis");
    if (data.count("status")) status = stringToConsultationStatus(std::stoi(data.at("status")));
    if (data.count("duration")) duration = std::stoi(data.at("duration"));
    if (data.count("created_at")) createdAt = data.at("created_at");
}

std::string Consultation::getCurrentTimestamp() const {
    std::time_t now = std::time(nullptr);
    char buf[20];
    std::strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", std::localtime(&now));
    return std::string(buf);
}
