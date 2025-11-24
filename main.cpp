#include "Navigator.h"
#include "Database.h"
#include "Patient.h"
#include "HealthProfessional.h"
#include "User.h"
#include "MedicalRecord.h"
#include "Antecedent.h"
#include "Consultation.h"
#include "Prescription.h"
#include "Exam.h"
#include "LoginWindow.h"
#include <memory>
#include <iostream>

int main() {
    // Initialiser la base de données
    Database& db = Database::getInstance();
    if (!db.connect("hospital.db")) {
        std::cerr << "Impossible de se connecter à la base de données" << std::endl;
        return 1;
    }
    
    // Créer les tables
    Patient::createTable();
    HealthProfessional::createTable();
    User::createTable();
    MedicalRecord::createTable();
    Antecedent::createTable();
    Consultation::createTable();
    Prescription::createTable();
    Exam::createTable();
    
    // Ajouter des données de test
    HealthProfessional::seedData();
    User::seedData();
    Patient::seedData();
    
    std::cout << "\n";
    
    // Lancer l'application avec LoginWindow
    Navigator navigator;
    navigator.push(std::make_unique<LoginWindow>(navigator));
    navigator.run();
    
    return 0;
}