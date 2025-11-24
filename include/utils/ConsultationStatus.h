#ifndef CONSULTATIONSTATUS_H
#define CONSULTATIONSTATUS_H

#include <string>

enum class ConsultationStatus {
    SCHEDULED = 0,
    COMPLETED = 1,
    CANCELLED = 2
};

enum class DayOfWeek {
    MONDAY = 0,
    TUESDAY = 1,
    WEDNESDAY = 2,
    THURSDAY = 3,
    FRIDAY = 4,
    SATURDAY = 5,
    SUNDAY = 6
};

// Conversion functions
std::string consultationStatusToString(ConsultationStatus status);
ConsultationStatus stringToConsultationStatus(int value);

std::string dayOfWeekToString(DayOfWeek day);
DayOfWeek stringToDayOfWeek(int value);

#endif // CONSULTATIONSTATUS_H
