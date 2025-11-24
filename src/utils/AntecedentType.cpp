#include "AntecedentType.h"

std::string antecedentTypeToString(AntecedentType type) {
    switch (type) {
        case AntecedentType::PATHOLOGY: return "Pathologie";
        case AntecedentType::SURGERY: return "Chirurgie";
        case AntecedentType::ALLERGY: return "Allergie";
        case AntecedentType::TREATMENT: return "Traitement";
        default: return "Inconnu";
    }
}

AntecedentType stringToAntecedentType(int value) {
    switch (value) {
        case 0: return AntecedentType::PATHOLOGY;
        case 1: return AntecedentType::SURGERY;
        case 2: return AntecedentType::ALLERGY;
        case 3: return AntecedentType::TREATMENT;
        default: return AntecedentType::PATHOLOGY;
    }
}

std::string severityToString(Severity severity) {
    switch (severity) {
        case Severity::LOW: return "Faible";
        case Severity::MEDIUM: return "Moyenne";
        case Severity::HIGH: return "Élevée";
        default: return "Inconnu";
    }
}

Severity stringToSeverity(int value) {
    switch (value) {
        case 0: return Severity::LOW;
        case 1: return Severity::MEDIUM;
        case 2: return Severity::HIGH;
        default: return Severity::LOW;
    }
}
