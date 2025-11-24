#include "User.h"
#include <iostream>
#include <functional>

User::User(int healthProfessionalId, const std::string& username, const std::string& password)
    : healthProfessionalId(healthProfessionalId), username(username) {
    setPassword(password);
}

bool User::checkPassword(const std::string& password) const {
    return hashPassword(password) == passwordHash;
}

void User::setPassword(const std::string& password) {
    passwordHash = hashPassword(password);
}

std::unique_ptr<HealthProfessional> User::getHealthProfessional() const {
    return HealthProfessional::find(healthProfessionalId);
}

std::unique_ptr<User> User::authenticate(const std::string& username, const std::string& password) {
    Database& db = Database::getInstance();
    std::string sql = "SELECT * FROM users WHERE username = '" + username + "'";
    auto results = db.query(sql);
    
    if (results.empty()) {
        return nullptr;
    }
    
    auto user = std::make_unique<User>();
    user->fromMap(results[0]);
    
    if (user->checkPassword(password)) {
        return user;
    }
    
    return nullptr;
}

void User::createTable() {
    Database& db = Database::getInstance();
    
    std::string sql = R"(
        CREATE TABLE IF NOT EXISTS users (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            health_professional_id INTEGER NOT NULL,
            username TEXT UNIQUE NOT NULL,
            password_hash TEXT NOT NULL,
            FOREIGN KEY (health_professional_id) REFERENCES health_professionals(id)
        )
    )";
    
    if (db.execute(sql)) {
        std::cout << "Table 'users' créée avec succès" << std::endl;
    }
}

void User::seedData() {
    auto existing = User::all();
    if (!existing.empty()) {
        std::cout << "Utilisateurs déjà présents" << std::endl;
        return;
    }
    
    // Récupérer les professionnels
    auto professionals = HealthProfessional::all();
    if (professionals.size() >= 3) {
        User(professionals[0].getId(), "admin", "admin123").save();
        User(professionals[1].getId(), "docteur", "doc123").save();
        User(professionals[2].getId(), "secretaire", "sec123").save();
        std::cout << "Utilisateurs créés (admin, docteur, secretaire)" << std::endl;
    }
}

std::string User::getTableName() const {
    return "users";
}

std::map<std::string, std::string> User::toMap() const {
    return {
        {"id", std::to_string(id)},
        {"health_professional_id", std::to_string(healthProfessionalId)},
        {"username", username},
        {"password_hash", passwordHash}
    };
}

void User::fromMap(const std::map<std::string, std::string>& data) {
    if (data.count("id")) id = std::stoi(data.at("id"));
    if (data.count("health_professional_id")) healthProfessionalId = std::stoi(data.at("health_professional_id"));
    if (data.count("username")) username = data.at("username");
    if (data.count("password_hash")) passwordHash = data.at("password_hash");
}

std::string User::hashPassword(const std::string& password) const {
    // Simple hash pour prototype (utiliser bcrypt en production)
    std::hash<std::string> hasher;
    return std::to_string(hasher(password + "salt_secret"));
}
