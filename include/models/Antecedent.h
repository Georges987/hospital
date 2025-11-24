#ifndef ANTECEDENT_H
#define ANTECEDENT_H

#include "Model.h"
#include "AntecedentType.h"
#include <string>

class Patient;

class Antecedent : public Model<Antecedent> {
public:
    Antecedent() = default;
    Antecedent(int patientId, AntecedentType type, const std::string& description,
               const std::string& date = "", Severity severity = Severity::MEDIUM);
    
    // Getters
    int getPatientId() const { return patientId; }
    AntecedentType getType() const { return type; }
    std::string getDescription() const { return description; }
    std::string getDate() const { return date; }
    Severity getSeverity() const { return severity; }
    bool getIsActive() const { return isActive; }
    
    // Setters
    void setType(AntecedentType t) { type = t; }
    void setDescription(const std::string& d) { description = d; }
    void setDate(const std::string& d) { date = d; }
    void setSeverity(Severity s) { severity = s; }
    void setIsActive(bool active) { isActive = active; }
    
    // Relations
    std::unique_ptr<Patient> getPatient() const;
    
    // Static methods
    static std::vector<Antecedent> findByPatient(int patientId);
    static std::vector<Antecedent> findActiveByPatient(int patientId);
    static std::vector<Antecedent> findByType(int patientId, AntecedentType type);
    static void createTable();
    
    // ORM
    std::string getTableName() const override;
    std::map<std::string, std::string> toMap() const override;
    void fromMap(const std::map<std::string, std::string>& data) override;
    
private:
    int patientId = 0;
    AntecedentType type = AntecedentType::PATHOLOGY;
    std::string description;
    std::string date;
    Severity severity = Severity::MEDIUM;
    bool isActive = true;
};

#endif // ANTECEDENT_H
