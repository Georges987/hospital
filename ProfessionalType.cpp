#include "ProfessionalType.h"

std::string professionalTypeToString(ProfessionalType type) {
    switch (type) {
        case ProfessionalType::ADMIN:
            return "Administrateur";
        case ProfessionalType::DOCTOR:
            return "Médecin";
        case ProfessionalType::SECRETARY:
            return "Secrétaire";
        default:
            return "Inconnu";
    }
}

ProfessionalType stringToProfessionalType(int value) {
    switch (value) {
        case 0: return ProfessionalType::ADMIN;
        case 1: return ProfessionalType::DOCTOR;
        case 2: return ProfessionalType::SECRETARY;
        default: return ProfessionalType::SECRETARY;
    }
}
