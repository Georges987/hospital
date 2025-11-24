#ifndef CONSULTATION_H
#define CONSULTATION_H

#include "Model.h"
#include "ConsultationStatus.h"
#include <string>

class Patient;
class HealthProfessional;

class Consultation : public Model<Consultation> {
public:
    Consultation() = default;
    Consultation(int patientId, int doctorId, const std::string& date,
                const std::string& time, const std::string& motif = "");
    
    // Getters
    int getPatientId() const { return patientId; }
    int getDoctorId() const { return doctorId; }
    std::string getDate() const { return date; }
    std::string getTime() const { return time; }
    std::string getMotif() const { return motif; }
    std::string getObservations() const { return observations; }
    std::string getDiagnosis() const { return diagnosis; }
    ConsultationStatus getStatus() const { return status; }
    int getDuration() const { return duration; }
    std::string getCreatedAt() const { return createdAt; }
    
    // Setters
    void setMotif(const std::string& m) { motif = m; }
    void setObservations(const std::string& o) { observations = o; }
    void setDiagnosis(const std::string& d) { diagnosis = d; }
    void setStatus(ConsultationStatus s) { status = s; }
    void setDuration(int d) { duration = d; }
    
    // Relations
    std::unique_ptr<Patient> getPatient() const;
    std::unique_ptr<HealthProfessional> getDoctor() const;
    
    // Static methods
    static std::vector<Consultation> findByPatient(int patientId);
    static std::vector<Consultation> findByDoctor(int doctorId);
    static std::vector<Consultation> findByDate(const std::string& date);
    static std::vector<Consultation> findUpcoming();
    static std::vector<Consultation> findByDateRange(const std::string& startDate, const std::string& endDate);
    static void createTable();
    
    // ORM
    std::string getTableName() const override;
    std::map<std::string, std::string> toMap() const override;
    void fromMap(const std::map<std::string, std::string>& data) override;
    
private:
    int patientId = 0;
    int doctorId = 0;
    std::string date;
    std::string time;
    std::string motif;
    std::string observations;
    std::string diagnosis;
    ConsultationStatus status = ConsultationStatus::SCHEDULED;
    int duration = 30; // minutes
    std::string createdAt;
    
    std::string getCurrentTimestamp() const;
};

#endif // CONSULTATION_H
