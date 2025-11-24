#ifndef PATIENT_H
#define PATIENT_H

#include "Model.h"
#include "Person.h"
#include <string>

class Patient : public Person, public Model<Patient> {
public:
    // Constructeurs
    Patient() = default;
    Patient(const std::string& nom, const std::string& prenom, int age, const std::string& telephone = "");
    
    // Getters spécifiques Patient
    int getAge() const { return age; }
    std::string getNumeroSecu() const { return numeroSecu; }
    std::string getAdresse() const { return adresse; }
    
    // Setters spécifiques Patient
    void setAge(int a) { age = a; }
    void setNumeroSecu(const std::string& n) { numeroSecu = n; }
    void setAdresse(const std::string& a) { adresse = a; }
    
    // Méthodes ORM (override)
    std::string getTableName() const override;
    std::map<std::string, std::string> toMap() const override;
    void fromMap(const std::map<std::string, std::string>& data) override;
    
    // Utilitaires statiques
    static void createTable();
    static void seedData();
    
private:
    int age = 0;
    std::string numeroSecu;
    std::string adresse;
};

#endif // PATIENT_H
