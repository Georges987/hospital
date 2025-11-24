#ifndef PROFESSIONALTYPE_H
#define PROFESSIONALTYPE_H

#include <string>

enum class ProfessionalType {
    ADMIN = 0,
    DOCTOR = 1,
    SECRETARY = 2
};

std::string professionalTypeToString(ProfessionalType type);
ProfessionalType stringToProfessionalType(int value);

#endif // PROFESSIONALTYPE_H
