#include "Patient.h"
#include <iostream>
#include <ctime>

Patient::Patient(const std::string& nom, const std::string& prenom, 
                 const std::string& dateNaissance, const std::string& sexe,
                 const std::string& telephone)
    : dateNaissance(dateNaissance), sexe(sexe) {
    this->nom = nom;
    this->prenom = prenom;
    this->telephone = telephone;
}

int Patient::getAge() const {
    if (dateNaissance.empty()) return 0;
    
    // Parse YYYY-MM-DD
    int year = std::stoi(dateNaissance.substr(0, 4));
    int month = std::stoi(dateNaissance.substr(5, 2));
    int day = std::stoi(dateNaissance.substr(8, 2));
    
    // Get current date
    std::time_t now = std::time(nullptr);
    std::tm* currentDate = std::localtime(&now);
    
    int age = currentDate->tm_year + 1900 - year;
    
    // Adjust if birthday hasn't occurred this year
    if (currentDate->tm_mon + 1 < month || 
        (currentDate->tm_mon + 1 == month && currentDate->tm_mday < day)) {
        age--;
    }
    
    return age;
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
        {"date_naissance", dateNaissance},
        {"sexe", sexe},
        {"groupe_sanguin", groupeSanguin},
        {"numero_secu", numeroSecu},
        {"adresse", adresse},
        {"email", email},
        {"contact_urgence", contactUrgence},
        {"telephone_urgence", telephoneUrgence}
    };
}

void Patient::fromMap(const std::map<std::string, std::string>& data) {
    if (data.count("id")) id = std::stoi(data.at("id"));
    if (data.count("nom")) nom = data.at("nom");
    if (data.count("prenom")) prenom = data.at("prenom");
    if (data.count("telephone")) telephone = data.at("telephone");
    if (data.count("date_naissance")) dateNaissance = data.at("date_naissance");
    if (data.count("sexe")) sexe = data.at("sexe");
    if (data.count("groupe_sanguin")) groupeSanguin = data.at("groupe_sanguin");
    if (data.count("numero_secu")) numeroSecu = data.at("numero_secu");
    if (data.count("adresse")) adresse = data.at("adresse");
    if (data.count("email")) email = data.at("email");
    if (data.count("contact_urgence")) contactUrgence = data.at("contact_urgence");
    if (data.count("telephone_urgence")) telephoneUrgence = data.at("telephone_urgence");
}

void Patient::createTable() {
    Database& db = Database::getInstance();
    
    std::string sql = R"(
        CREATE TABLE IF NOT EXISTS patients (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            nom TEXT NOT NULL,
            prenom TEXT NOT NULL,
            telephone TEXT,
            date_naissance TEXT NOT NULL,
            sexe TEXT NOT NULL,
            groupe_sanguin TEXT,
            numero_secu TEXT,
            adresse TEXT,
            email TEXT,
            contact_urgence TEXT,
            telephone_urgence TEXT
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
        Patient("Dupont", "Jean", "1978-05-15", "M", "0123456789"),
        Patient("Martin", "Marie", "1992-08-22", "F", "0234567890"),
        Patient("Durand", "Pierre", "1965-12-03", "M", "0345678901"),
        Patient("Bernard", "Sophie", "1983-03-18", "F", "0456789012"),
        Patient("Petit", "Lucas", "1995-11-07", "M", "0567890123")
    };
    
    for (auto& patient : patients) {
        if (patient.save()) {
            std::cout << "Patient ajouté: " << patient.getFullName() << " (" << patient.getAge() << " ans)" << std::endl;
        }
    }
}

