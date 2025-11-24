#ifndef STATISTICS_H
#define STATISTICS_H

#include "ProfessionalType.h"
#include <map>
#include <string>
#include <vector>

class Statistics {
public:
    // Patients
    static int getTotalPatients();
    static int getPatientsBySex(const std::string& sex);
    static int getPatientsByAgeRange(int minAge, int maxAge);
    
    // Professionnels
    static int getTotalProfessionals();
    static std::map<ProfessionalType, int> getProfessionalsByType();
    static int getActiveProfessionals();
    
    // Antécédents
    static int getTotalAntecedents();
    static int getActiveAntecedents();
    static std::map<std::string, int> getAntecedentsByType();
    
    // Dossiers médicaux
    static int getTotalMedicalRecords();
    static int getRecordsWithDoctor();
    
    // Consultations
    static int getTotalConsultations();
    static int getScheduledConsultations();
    static int getCompletedConsultations();
    static int getConsultationsByDateRange(const std::string& startDate, const std::string& endDate);
    
    // Utilisateurs
    static int getTotalUsers();
    static int getActiveUsers();
};

#endif // STATISTICS_H
