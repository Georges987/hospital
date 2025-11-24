#include "Exam.h"
#include "Consultation.h"
#include <iostream>
#include <ctime>

Exam::Exam(int consultationId, const std::string& examType,
          const std::string& results)
    : consultationId(consultationId), examType(examType), results(results) {
    createdAt = getCurrentTimestamp();
}

std::unique_ptr<Consultation> Exam::getConsultation() const {
    return Consultation::find(consultationId);
}

std::vector<Exam> Exam::findByConsultation(int consultationId) {
    Database& db = Database::getInstance();
    std::string sql = "SELECT * FROM exams WHERE consultation_id = " + std::to_string(consultationId);
    auto results = db.query(sql);
    
    std::vector<Exam> exams;
    for (const auto& row : results) {
        Exam exam;
        exam.fromMap(row);
        exams.push_back(exam);
    }
    
    return exams;
}

std::vector<Exam> Exam::findByPatient(int patientId) {
    Database& db = Database::getInstance();
    std::string sql = R"(
        SELECT e.* FROM exams e
        JOIN consultations c ON e.consultation_id = c.id
        WHERE c.patient_id = )" + std::to_string(patientId) + 
        " ORDER BY e.exam_date DESC, e.created_at DESC";
    auto results = db.query(sql);
    
    std::vector<Exam> exams;
    for (const auto& row : results) {
        Exam exam;
        exam.fromMap(row);
        exams.push_back(exam);
    }
    
    return exams;
}

void Exam::createTable() {
    Database& db = Database::getInstance();
    
    std::string sql = R"(
        CREATE TABLE IF NOT EXISTS exams (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            consultation_id INTEGER NOT NULL,
            exam_type TEXT NOT NULL,
            results TEXT NOT NULL,
            notes TEXT,
            exam_date TEXT,
            created_at TEXT NOT NULL,
            FOREIGN KEY (consultation_id) REFERENCES consultations(id)
        )
    )";
    
    if (db.execute(sql)) {
        std::cout << "Table 'exams' créée avec succès" << std::endl;
    } else {
        std::cerr << "Erreur création table 'exams': " << db.getLastError() << std::endl;
    }
}

std::string Exam::getTableName() const {
    return "exams";
}

std::map<std::string, std::string> Exam::toMap() const {
    return {
        {"id", std::to_string(id)},
        {"consultation_id", std::to_string(consultationId)},
        {"exam_type", examType},
        {"results", results},
        {"notes", notes},
        {"exam_date", examDate},
        {"created_at", createdAt}
    };
}

void Exam::fromMap(const std::map<std::string, std::string>& data) {
    if (data.count("id")) id = std::stoi(data.at("id"));
    if (data.count("consultation_id")) consultationId = std::stoi(data.at("consultation_id"));
    if (data.count("exam_type")) examType = data.at("exam_type");
    if (data.count("results")) results = data.at("results");
    if (data.count("notes")) notes = data.at("notes");
    if (data.count("exam_date")) examDate = data.at("exam_date");
    if (data.count("created_at")) createdAt = data.at("created_at");
}

std::string Exam::getCurrentTimestamp() const {
    std::time_t now = std::time(nullptr);
    char buf[20];
    std::strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", std::localtime(&now));
    return std::string(buf);
}
