#include "AuthService.h"

AuthService& AuthService::getInstance() {
    static AuthService instance;
    return instance;
}

bool AuthService::login(const std::string& username, const std::string& password) {
    auto user = User::authenticate(username, password);
    if (!user) {
        return false;
    }
    
    currentUser = std::move(user);
    currentProfessional = currentUser->getHealthProfessional();
    
    return currentProfessional != nullptr;
}

void AuthService::logout() {
    currentUser.reset();
    currentProfessional.reset();
}

bool AuthService::isAuthenticated() const {
    return currentUser != nullptr && currentProfessional != nullptr;
}

User* AuthService::getCurrentUser() const {
    return currentUser.get();
}

HealthProfessional* AuthService::getCurrentProfessional() const {
    return currentProfessional.get();
}

ProfessionalType AuthService::getCurrentType() const {
    if (currentProfessional) {
        return currentProfessional->getType();
    }
    return ProfessionalType::SECRETARY; // Default
}

bool AuthService::hasPermission(ProfessionalType requiredType) const {
    if (!isAuthenticated()) {
        return false;
    }
    
    auto currentType = getCurrentType();
    
    // Admin a tous les droits
    if (currentType == ProfessionalType::ADMIN) {
        return true;
    }
    
    // Sinon, vérifier le type exact
    return currentType == requiredType;
}
