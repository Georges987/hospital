#ifndef PATIENT_H
#define PATIENT_H

#include "Model.h"
#include "Person.h"
#include <string>

class Patient : public Person, public Model<Patient> {
public:
    // Constructeurs
    Patient() = default;
    Patient(const std::string& nom, const std::string& prenom, 
            const std::string& dateNaissance, const std::string& sexe,
            const std::string& telephone = "");
    
    // Getters spécifiques Patient
    std::string getDateNaissance() const { return dateNaissance; }
    std::string getSexe() const { return sexe; }
    std::string getGroupeSanguin() const { return groupeSanguin; }
    std::string getNumeroSecu() const { return numeroSecu; }
    std::string getAdresse() const { return adresse; }
    std::string getEmail() const { return email; }
    std::string getContactUrgence() const { return contactUrgence; }
    std::string getTelephoneUrgence() const { return telephoneUrgence; }
    int getAge() const; // Calculé à partir de dateNaissance
    
    // Setters spécifiques Patient
    void setDateNaissance(const std::string& d) { dateNaissance = d; }
    void setSexe(const std::string& s) { sexe = s; }
    void setGroupeSanguin(const std::string& g) { groupeSanguin = g; }
    void setNumeroSecu(const std::string& n) { numeroSecu = n; }
    void setAdresse(const std::string& a) { adresse = a; }
    void setEmail(const std::string& e) { email = e; }
    void setContactUrgence(const std::string& c) { contactUrgence = c; }
    void setTelephoneUrgence(const std::string& t) { telephoneUrgence = t; }
    
    // Méthodes ORM (override)
    std::string getTableName() const override;
    std::map<std::string, std::string> toMap() const override;
    void fromMap(const std::map<std::string, std::string>& data) override;
    
    // Utilitaires statiques
    static void createTable();
    static void seedData();
    
private:
    std::string dateNaissance;      // Format: YYYY-MM-DD
    std::string sexe;                // M, F, Autre
    std::string groupeSanguin;       // A+, A-, B+, B-, AB+, AB-, O+, O-
    std::string numeroSecu;
    std::string adresse;
    std::string email;
    std::string contactUrgence;      // Nom du contact
    std::string telephoneUrgence;    // Téléphone du contact
};

#endif // PATIENT_H
