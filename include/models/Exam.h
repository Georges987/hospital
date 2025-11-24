#ifndef EXAM_H
#define EXAM_H

#include "Model.h"
#include <string>

class Patient;
class Consultation;

class Exam : public Model<Exam> {
public:
    Exam() = default;
    Exam(int consultationId, const std::string& examType,
         const std::string& results);
    
    // Getters
    int getConsultationId() const { return consultationId; }
    std::string getExamType() const { return examType; }
    std::string getResults() const { return results; }
    std::string getNotes() const { return notes; }
    std::string getExamDate() const { return examDate; }
    std::string getCreatedAt() const { return createdAt; }
    
    // Setters
    void setResults(const std::string& r) { results = r; }
    void setNotes(const std::string& n) { notes = n; }
    void setExamDate(const std::string& d) { examDate = d; }
    
    // Relations
    std::unique_ptr<Consultation> getConsultation() const;
    
    // Static methods
    static std::vector<Exam> findByConsultation(int consultationId);
    static std::vector<Exam> findByPatient(int patientId);
    static void createTable();
    
    // ORM
    std::string getTableName() const override;
    std::map<std::string, std::string> toMap() const override;
    void fromMap(const std::map<std::string, std::string>& data) override;
    
private:
    int consultationId = 0;
    std::string examType;
    std::string results;
    std::string notes;
    std::string examDate;
    std::string createdAt;
    
    std::string getCurrentTimestamp() const;
};

#endif // EXAM_H
