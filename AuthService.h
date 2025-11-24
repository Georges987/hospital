#ifndef AUTHSERVICE_H
#define AUTHSERVICE_H

#include "User.h"
#include "HealthProfessional.h"
#include "ProfessionalType.h"
#include <memory>

class AuthService {
public:
    static AuthService& getInstance();
    
    bool login(const std::string& username, const std::string& password);
    void logout();
    bool isAuthenticated() const;
    
    User* getCurrentUser() const;
    HealthProfessional* getCurrentProfessional() const;
    ProfessionalType getCurrentType() const;
    
    bool hasPermission(ProfessionalType requiredType) const;
    
private:
    AuthService() = default;
    ~AuthService() = default;
    AuthService(const AuthService&) = delete;
    AuthService& operator=(const AuthService&) = delete;
    
    std::unique_ptr<User> currentUser;
    std::unique_ptr<HealthProfessional> currentProfessional;
};

#endif // AUTHSERVICE_H
