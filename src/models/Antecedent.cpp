#include "Antecedent.h"
#include "Patient.h"
#include <iostream>

Antecedent::Antecedent(int patientId, AntecedentType type, const std::string& description,
                       const std::string& date, Severity severity)
    : patientId(patientId), type(type), description(description), 
      date(date), severity(severity) {}

std::unique_ptr<Patient> Antecedent::getPatient() const {
    return Patient::find(patientId);
}

std::vector<Antecedent> Antecedent::findByPatient(int patientId) {
    Database& db = Database::getInstance();
    std::string sql = "SELECT * FROM antecedents WHERE patient_id = " + std::to_string(patientId);
    auto results = db.query(sql);
    
    std::vector<Antecedent> antecedents;
    for (const auto& row : results) {
        Antecedent antecedent;
        antecedent.fromMap(row);
        antecedents.push_back(antecedent);
    }
    
    return antecedents;
}

std::vector<Antecedent> Antecedent::findActiveByPatient(int patientId) {
    Database& db = Database::getInstance();
    std::string sql = "SELECT * FROM antecedents WHERE patient_id = " + std::to_string(patientId) + 
                     " AND is_active = 1";
    auto results = db.query(sql);
    
    std::vector<Antecedent> antecedents;
    for (const auto& row : results) {
        Antecedent antecedent;
        antecedent.fromMap(row);
        antecedents.push_back(antecedent);
    }
    
    return antecedents;
}

std::vector<Antecedent> Antecedent::findByType(int patientId, AntecedentType type) {
    Database& db = Database::getInstance();
    std::string sql = "SELECT * FROM antecedents WHERE patient_id = " + std::to_string(patientId) + 
                     " AND type = " + std::to_string(static_cast<int>(type));
    auto results = db.query(sql);
    
    std::vector<Antecedent> antecedents;
    for (const auto& row : results) {
        Antecedent antecedent;
        antecedent.fromMap(row);
        antecedents.push_back(antecedent);
    }
    
    return antecedents;
}

void Antecedent::createTable() {
    Database& db = Database::getInstance();
    
    std::string sql = R"(
        CREATE TABLE IF NOT EXISTS antecedents (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            patient_id INTEGER NOT NULL,
            type INTEGER NOT NULL,
            description TEXT NOT NULL,
            date TEXT,
            severity INTEGER DEFAULT 1,
            is_active INTEGER DEFAULT 1,
            FOREIGN KEY (patient_id) REFERENCES patients(id)
        )
    )";
    
    if (db.execute(sql)) {
        std::cout << "Table 'antecedents' créée avec succès" << std::endl;
    } else {
        std::cerr << "Erreur création table 'antecedents': " << db.getLastError() << std::endl;
    }
}

std::string Antecedent::getTableName() const {
    return "antecedents";
}

std::map<std::string, std::string> Antecedent::toMap() const {
    return {
        {"id", std::to_string(id)},
        {"patient_id", std::to_string(patientId)},
        {"type", std::to_string(static_cast<int>(type))},
        {"description", description},
        {"date", date},
        {"severity", std::to_string(static_cast<int>(severity))},
        {"is_active", isActive ? "1" : "0"}
    };
}

void Antecedent::fromMap(const std::map<std::string, std::string>& data) {
    if (data.count("id")) id = std::stoi(data.at("id"));
    if (data.count("patient_id")) patientId = std::stoi(data.at("patient_id"));
    if (data.count("type")) type = stringToAntecedentType(std::stoi(data.at("type")));
    if (data.count("description")) description = data.at("description");
    if (data.count("date")) date = data.at("date");
    if (data.count("severity")) severity = stringToSeverity(std::stoi(data.at("severity")));
    if (data.count("is_active")) isActive = (data.at("is_active") == "1");
}
