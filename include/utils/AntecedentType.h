#ifndef ANTECEDENTTYPE_H
#define ANTECEDENTTYPE_H

#include <string>

enum class AntecedentType {
    PATHOLOGY = 0,      // Pathologie
    SURGERY = 1,        // Chirurgie
    ALLERGY = 2,        // Allergie
    TREATMENT = 3       // Traitement antérieur
};

enum class Severity {
    LOW = 0,
    MEDIUM = 1,
    HIGH = 2
};

// Conversion functions
std::string antecedentTypeToString(AntecedentType type);
AntecedentType stringToAntecedentType(int value);

std::string severityToString(Severity severity);
Severity stringToSeverity(int value);

#endif // ANTECEDENTTYPE_H
