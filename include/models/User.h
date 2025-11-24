#ifndef USER_H
#define USER_H

#include "Model.h"
#include "HealthProfessional.h"
#include <string>
#include <memory>

class User : public Model<User> {
public:
    User() = default;
    User(int healthProfessionalId, const std::string& username, const std::string& password);
    
    // Getters
    std::string getUsername() const { return username; }
    int getHealthProfessionalId() const { return healthProfessionalId; }
    
    // Authentication
    bool checkPassword(const std::string& password) const;
    void setPassword(const std::string& password);
    
    // Relations
    std::unique_ptr<HealthProfessional> getHealthProfessional() const;
    
    // Static
    static std::unique_ptr<User> authenticate(const std::string& username, const std::string& password);
    static void createTable();
    static void seedData();
    
    // ORM
    std::string getTableName() const override;
    std::map<std::string, std::string> toMap() const override;
    void fromMap(const std::map<std::string, std::string>& data) override;
    
private:
    int healthProfessionalId = 0;
    std::string username;
    std::string passwordHash;
    
    std::string hashPassword(const std::string& password) const;
};

#endif // USER_H
