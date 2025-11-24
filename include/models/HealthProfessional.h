#ifndef HEALTHPROFESSIONAL_H
#define HEALTHPROFESSIONAL_H

#include "Model.h"
#include "Person.h"
#include "ProfessionalType.h"
#include <string>

class HealthProfessional : public Person, public Model<HealthProfessional> {
public:
    // Constructeurs
    HealthProfessional() = default;
    HealthProfessional(const std::string& nom, const std::string& prenom,
                      const std::string& email, ProfessionalType type);
    
    // Getters
    std::string getEmail() const { return email; }
    ProfessionalType getType() const { return type; }
    std::string getNumeroLicence() const { return numeroLicence; }
    std::string getSpecialite() const { return specialite; }
    std::string getService() const { return service; }
    std::string getDepartment() const { return department; }
    std::string getDateEmbauche() const { return dateEmbauche; }
    bool getIsActive() const { return isActive; }
    bool getHasMedicalDataAccess() const { return hasMedicalDataAccess; }
    
    // Setters
    void setEmail(const std::string& e) { email = e; }
    void setType(ProfessionalType t) { type = t; }
    void setNumeroLicence(const std::string& n) { numeroLicence = n; }
    void setSpecialite(const std::string& s) { specialite = s; }
    void setService(const std::string& s) { service = s; }
    void setDepartment(const std::string& d) { department = d; }
    void setDateEmbauche(const std::string& d) { dateEmbauche = d; }
    void setIsActive(bool a) { isActive = a; }
    void setHasMedicalDataAccess(bool access) { hasMedicalDataAccess = access; }
    
    // ORM methods
    std::string getTableName() const override;
    std::map<std::string, std::string> toMap() const override;
    void fromMap(const std::map<std::string, std::string>& data) override;
    
    // Static methods
    static void createTable();
    static void seedData();
    
private:
    std::string email;
    ProfessionalType type = ProfessionalType::SECRETARY;
    std::string numeroLicence;      // Numéro de licence professionnelle (générique)
    std::string specialite;          // Pour DOCTOR
    std::string service;             // Pour SECRETARY
    std::string department;          // Pour ADMIN
    std::string dateEmbauche;        // Date d'embauche
    bool isActive = true;            // Statut actif/inactif
    bool hasMedicalDataAccess = false; // Habilitation accès données médicales
};

#endif // HEALTHPROFESSIONAL_H
