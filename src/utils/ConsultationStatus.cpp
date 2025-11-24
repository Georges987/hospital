#include "ConsultationStatus.h"

std::string consultationStatusToString(ConsultationStatus status) {
    switch (status) {
        case ConsultationStatus::SCHEDULED: return "Programmée";
        case ConsultationStatus::COMPLETED: return "Terminée";
        case ConsultationStatus::CANCELLED: return "Annulée";
        default: return "Inconnu";
    }
}

ConsultationStatus stringToConsultationStatus(int value) {
    switch (value) {
        case 0: return ConsultationStatus::SCHEDULED;
        case 1: return ConsultationStatus::COMPLETED;
        case 2: return ConsultationStatus::CANCELLED;
        default: return ConsultationStatus::SCHEDULED;
    }
}

std::string dayOfWeekToString(DayOfWeek day) {
    switch (day) {
        case DayOfWeek::MONDAY: return "Lundi";
        case DayOfWeek::TUESDAY: return "Mardi";
        case DayOfWeek::WEDNESDAY: return "Mercredi";
        case DayOfWeek::THURSDAY: return "Jeudi";
        case DayOfWeek::FRIDAY: return "Vendredi";
        case DayOfWeek::SATURDAY: return "Samedi";
        case DayOfWeek::SUNDAY: return "Dimanche";
        default: return "Inconnu";
    }
}

DayOfWeek stringToDayOfWeek(int value) {
    switch (value) {
        case 0: return DayOfWeek::MONDAY;
        case 1: return DayOfWeek::TUESDAY;
        case 2: return DayOfWeek::WEDNESDAY;
        case 3: return DayOfWeek::THURSDAY;
        case 4: return DayOfWeek::FRIDAY;
        case 5: return DayOfWeek::SATURDAY;
        case 6: return DayOfWeek::SUNDAY;
        default: return DayOfWeek::MONDAY;
    }
}
