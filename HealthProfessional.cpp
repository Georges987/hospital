#include "HealthProfessional.h"
#include <iostream>

HealthProfessional::HealthProfessional(const std::string& nom, const std::string& prenom,
                                      const std::string& email, ProfessionalType type)
    : email(email), type(type) {
    this->nom = nom;
    this->prenom = prenom;
}

std::string HealthProfessional::getTableName() const {
    return "health_professionals";
}

std::map<std::string, std::string> HealthProfessional::toMap() const {
    return {
        {"id", std::to_string(id)},
        {"nom", nom},
        {"prenom", prenom},
        {"telephone", telephone},
        {"email", email},
        {"type", std::to_string(static_cast<int>(type))},
        {"specialite", specialite},
        {"numero_ordre", numeroOrdre},
        {"service", service},
        {"department", department}
    };
}

void HealthProfessional::fromMap(const std::map<std::string, std::string>& data) {
    if (data.count("id")) id = std::stoi(data.at("id"));
    if (data.count("nom")) nom = data.at("nom");
    if (data.count("prenom")) prenom = data.at("prenom");
    if (data.count("telephone")) telephone = data.at("telephone");
    if (data.count("email")) email = data.at("email");
    if (data.count("type")) type = stringToProfessionalType(std::stoi(data.at("type")));
    if (data.count("specialite")) specialite = data.at("specialite");
    if (data.count("numero_ordre")) numeroOrdre = data.at("numero_ordre");
    if (data.count("service")) service = data.at("service");
    if (data.count("department")) department = data.at("department");
}

void HealthProfessional::createTable() {
    Database& db = Database::getInstance();
    
    std::string sql = R"(
        CREATE TABLE IF NOT EXISTS health_professionals (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            nom TEXT NOT NULL,
            prenom TEXT NOT NULL,
            telephone TEXT,
            email TEXT UNIQUE NOT NULL,
            type INTEGER NOT NULL,
            specialite TEXT,
            numero_ordre TEXT,
            service TEXT,
            department TEXT
        )
    )";
    
    if (db.execute(sql)) {
        std::cout << "Table 'health_professionals' créée avec succès" << std::endl;
    }
}

void HealthProfessional::seedData() {
    auto existing = HealthProfessional::all();
    if (!existing.empty()) {
        std::cout << "Professionnels de santé déjà présents" << std::endl;
        return;
    }
    
    // Admin
    HealthProfessional admin("Admin", "Système", "admin@hospital.com", ProfessionalType::ADMIN);
    admin.setDepartment("IT");
    admin.save();
    
    // Docteur
    HealthProfessional doctor("Leblanc", "Pierre", "p.leblanc@hospital.com", ProfessionalType::DOCTOR);
    doctor.setSpecialite("Cardiologie");
    doctor.setNumeroOrdre("12345");
    doctor.save();
    
    // Secrétaire
    HealthProfessional secretary("Moreau", "Julie", "j.moreau@hospital.com", ProfessionalType::SECRETARY);
    secretary.setService("Accueil");
    secretary.save();
    
    std::cout << "Professionnels de santé créés" << std::endl;
}
