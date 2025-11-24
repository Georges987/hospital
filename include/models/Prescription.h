#ifndef PRESCRIPTION_H
#define PRESCRIPTION_H

#include "Model.h"
#include <string>

class Patient;
class HealthProfessional;
class Consultation;

class Prescription : public Model<Prescription> {
public:
    Prescription() = default;
    Prescription(int consultationId, const std::string& medication,
                const std::string& dosage, int durationDays);
    
    // Getters
    int getConsultationId() const { return consultationId; }
    std::string getMedication() const { return medication; }
    std::string getDosage() const { return dosage; }
    int getDurationDays() const { return durationDays; }
    std::string getInstructions() const { return instructions; }
    std::string getCreatedAt() const { return createdAt; }
    
    // Setters
    void setInstructions(const std::string& i) { instructions = i; }
    
    // Relations
    std::unique_ptr<Consultation> getConsultation() const;
    
    // Static methods
    static std::vector<Prescription> findByConsultation(int consultationId);
    static std::vector<Prescription> findByPatient(int patientId);
    static void createTable();
    
    // ORM
    std::string getTableName() const override;
    std::map<std::string, std::string> toMap() const override;
    void fromMap(const std::map<std::string, std::string>& data) override;
    
private:
    int consultationId = 0;
    std::string medication;
    std::string dosage;
    int durationDays = 0;
    std::string instructions;
    std::string createdAt;
    
    std::string getCurrentTimestamp() const;
};

#endif // PRESCRIPTION_H
