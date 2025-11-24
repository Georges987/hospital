#ifndef DATABASE_H
#define DATABASE_H

#include <sqlite3.h>
#include <string>
#include <vector>
#include <map>

class Database {
public:
    // Singleton
    static Database& getInstance();
    
    // Connexion
    bool connect(const std::string& dbPath);
    void disconnect();
    
    // Exécution de requêtes
    bool execute(const std::string& query);
    std::vector<std::map<std::string, std::string>> query(const std::string& sql);
    
    // Préparation de statements
    sqlite3_stmt* prepare(const std::string& query);
    
    // Utilitaires
    int getLastInsertId();
    std::string getLastError() const;
    
private:
    Database() = default;
    ~Database();
    
    // Empêcher la copie
    Database(const Database&) = delete;
    Database& operator=(const Database&) = delete;
    
    sqlite3* db = nullptr;
    std::string lastError;
};

#endif // DATABASE_H
