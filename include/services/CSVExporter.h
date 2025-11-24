#ifndef CSVEXPORTER_H
#define CSVEXPORTER_H

#include <string>
#include <vector>

class CSVExporter {
public:
    // Export patients to CSV
    static bool exportPatients(const std::string& filename);
    
    // Export consultations to CSV
    static bool exportConsultations(const std::string& filename);
    
    // Export statistics summary to CSV
    static bool exportStatistics(const std::string& filename);
    
private:
    static std::string escapeCSV(const std::string& value);
    static bool writeToFile(const std::string& filename, const std::vector<std::string>& lines);
};

#endif // CSVEXPORTER_H
