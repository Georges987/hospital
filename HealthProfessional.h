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
    std::string getSpecialite() const { return specialite; }
    std::string getNumeroOrdre() const { return numeroOrdre; }
    std::string getService() const { return service; }
    std::string getDepartment() const { return department; }
    
    // Setters
    void setEmail(const std::string& e) { email = e; }
    void setType(ProfessionalType t) { type = t; }
    void setSpecialite(const std::string& s) { specialite = s; }
    void setNumeroOrdre(const std::string& n) { numeroOrdre = n; }
    void setService(const std::string& s) { service = s; }
    void setDepartment(const std::string& d) { department = d; }
    
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
    
    // Attributs spécifiques selon le type
    std::string specialite;    // Pour DOCTOR
    std::string numeroOrdre;   // Pour DOCTOR
    std::string service;       // Pour SECRETARY
    std::string department;    // Pour ADMIN
};

#endif // HEALTHPROFESSIONAL_H
