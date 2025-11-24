#ifndef MEDICALRECORD_H
#define MEDICALRECORD_H

#include "Model.h"
#include <string>
#include <memory>

class Patient;
class HealthProfessional;

class MedicalRecord : public Model<MedicalRecord> {
public:
    MedicalRecord() = default;
    MedicalRecord(int patientId, int doctorId, const std::string& diagnosis = "", 
                  const std::string& treatment = "", const std::string& notes = "");
    
    // Getters
    int getPatientId() const { return patientId; }
    int getDoctorId() const { return doctorId; }
    std::string getDiagnosis() const { return diagnosis; }
    std::string getTreatment() const { return treatment; }
    std::string getNotes() const { return notes; }
    std::string getCreatedAt() const { return createdAt; }
    std::string getUpdatedAt() const { return updatedAt; }
    
    // Setters
    void setDoctorId(int id) { doctorId = id; }
    void setDiagnosis(const std::string& d) { diagnosis = d; }
    void setTreatment(const std::string& t) { treatment = t; }
    void setNotes(const std::string& n) { notes = n; }
    
    // Relations
    std::unique_ptr<Patient> getPatient() const;
    std::unique_ptr<HealthProfessional> getDoctor() const;
    
    // Static methods
    static std::vector<MedicalRecord> findByPatient(int patientId);
    static std::vector<MedicalRecord> findByDoctor(int doctorId);
    static void createTable();
    
    // ORM
    std::string getTableName() const override;
    std::map<std::string, std::string> toMap() const override;
    void fromMap(const std::map<std::string, std::string>& data) override;
    
private:
    int patientId = 0;
    int doctorId = 0;
    std::string diagnosis;
    std::string treatment;
    std::string notes;
    std::string createdAt;
    std::string updatedAt;
    
    std::string getCurrentTimestamp() const;
};

#endif // MEDICALRECORD_H
