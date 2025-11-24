#include "HealthProfessional.h"
#include <iostream>
#include <ctime>

HealthProfessional::HealthProfessional(const std::string& nom, const std::string& prenom,
                                      const std::string& email, ProfessionalType type)
    : email(email), type(type) {
    this->nom = nom;
    this->prenom = prenom;
    
    // Auto-assign medical data access for doctors
    if (type == ProfessionalType::DOCTOR) {
        hasMedicalDataAccess = true;
    }
    
    // Set hire date to current date
    std::time_t now = std::time(nullptr);
    char buf[11];
    std::strftime(buf, sizeof(buf), "%Y-%m-%d", std::localtime(&now));
    dateEmbauche = std::string(buf);
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
        {"numero_licence", numeroLicence},
        {"specialite", specialite},
        {"service", service},
        {"department", department},
        {"date_embauche", dateEmbauche},
        {"is_active", isActive ? "1" : "0"},
        {"has_medical_data_access", hasMedicalDataAccess ? "1" : "0"}
    };
}

void HealthProfessional::fromMap(const std::map<std::string, std::string>& data) {
    if (data.count("id")) id = std::stoi(data.at("id"));
    if (data.count("nom")) nom = data.at("nom");
    if (data.count("prenom")) prenom = data.at("prenom");
    if (data.count("telephone")) telephone = data.at("telephone");
    if (data.count("email")) email = data.at("email");
    if (data.count("type")) type = stringToProfessionalType(std::stoi(data.at("type")));
    if (data.count("numero_licence")) numeroLicence = data.at("numero_licence");
    if (data.count("specialite")) specialite = data.at("specialite");
    if (data.count("service")) service = data.at("service");
    if (data.count("department")) department = data.at("department");
    if (data.count("date_embauche")) dateEmbauche = data.at("date_embauche");
    if (data.count("is_active")) isActive = (data.at("is_active") == "1");
    if (data.count("has_medical_data_access")) hasMedicalDataAccess = (data.at("has_medical_data_access") == "1");
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
            numero_licence TEXT,
            specialite TEXT,
            service TEXT,
            department TEXT,
            date_embauche TEXT,
            is_active INTEGER DEFAULT 1,
            has_medical_data_access INTEGER DEFAULT 0
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
    admin.setNumeroLicence("ADM-001");
    admin.save();
    
    // Docteur
    HealthProfessional doctor("Leblanc", "Pierre", "p.leblanc@hospital.com", ProfessionalType::DOCTOR);
    doctor.setSpecialite("Cardiologie");
    doctor.setNumeroLicence("DOC-12345");
    doctor.save();
    
    // Secrétaire
    HealthProfessional secretary("Moreau", "Julie", "j.moreau@hospital.com", ProfessionalType::SECRETARY);
    secretary.setService("Accueil");
    secretary.setNumeroLicence("SEC-789");
    secretary.save();
    
    std::cout << "Professionnels de santé créés" << std::endl;
}

