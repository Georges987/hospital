#include "Patient.h"
#include <iostream>

Patient::Patient(const std::string& nom, const std::string& prenom, int age, const std::string& telephone)
    : age(age) {
    this->nom = nom;
    this->prenom = prenom;
    this->telephone = telephone;
}

std::string Patient::getTableName() const {
    return "patients";
}

std::map<std::string, std::string> Patient::toMap() const {
    return {
        {"id", std::to_string(id)},
        {"nom", nom},
        {"prenom", prenom},
        {"telephone", telephone},
        {"age", std::to_string(age)},
        {"numero_secu", numeroSecu},
        {"adresse", adresse}
    };
}

void Patient::fromMap(const std::map<std::string, std::string>& data) {
    if (data.count("id")) {
        id = std::stoi(data.at("id"));
    }
    if (data.count("nom")) {
        nom = data.at("nom");
    }
    if (data.count("prenom")) {
        prenom = data.at("prenom");
    }
    if (data.count("telephone")) {
        telephone = data.at("telephone");
    }
    if (data.count("age")) {
        age = std::stoi(data.at("age"));
    }
    if (data.count("numero_secu")) {
        numeroSecu = data.at("numero_secu");
    }
    if (data.count("adresse")) {
        adresse = data.at("adresse");
    }
}

void Patient::createTable() {
    Database& db = Database::getInstance();
    
    std::string sql = R"(
        CREATE TABLE IF NOT EXISTS patients (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            nom TEXT NOT NULL,
            prenom TEXT NOT NULL,
            telephone TEXT,
            age INTEGER,
            numero_secu TEXT,
            adresse TEXT
        )
    )";
    
    if (db.execute(sql)) {
        std::cout << "Table 'patients' créée avec succès" << std::endl;
    } else {
        std::cerr << "Erreur création table 'patients': " << db.getLastError() << std::endl;
    }
}

void Patient::seedData() {
    // Vérifier si des données existent déjà
    auto existing = Patient::all();
    if (!existing.empty()) {
        std::cout << "Données patients déjà présentes (" << existing.size() << " patients)" << std::endl;
        return;
    }
    
    // Ajouter des données de test
    std::vector<Patient> patients = {
        Patient("Dupont", "Jean", 45, "0123456789"),
        Patient("Martin", "Marie", 32, "0234567890"),
        Patient("Durand", "Pierre", 58, "0345678901"),
        Patient("Bernard", "Sophie", 41, "0456789012"),
        Patient("Petit", "Lucas", 29, "0567890123")
    };
    
    for (auto& patient : patients) {
        if (patient.save()) {
            std::cout << "Patient ajouté: " << patient.getFullName() << std::endl;
        }
    }
}
