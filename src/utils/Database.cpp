#include "Database.h"
#include <iostream>

Database& Database::getInstance() {
    static Database instance;
    return instance;
}

Database::~Database() {
    disconnect();
}

bool Database::connect(const std::string& dbPath) {
    if (db != nullptr) {
        return true; // Déjà connecté
    }
    
    int result = sqlite3_open(dbPath.c_str(), &db);
    if (result != SQLITE_OK) {
        lastError = sqlite3_errmsg(db);
        std::cerr << "Erreur connexion DB: " << lastError << std::endl;
        return false;
    }
    
    std::cout << "Connexion à la base de données réussie: " << dbPath << std::endl;
    return true;
}

void Database::disconnect() {
    if (db != nullptr) {
        sqlite3_close(db);
        db = nullptr;
    }
}

bool Database::execute(const std::string& query) {
    char* errorMsg = nullptr;
    int result = sqlite3_exec(db, query.c_str(), nullptr, nullptr, &errorMsg);
    
    if (result != SQLITE_OK) {
        lastError = errorMsg ? errorMsg : "Unknown error";
        std::cerr << "Erreur SQL: " << lastError << std::endl;
        if (errorMsg) {
            sqlite3_free(errorMsg);
        }
        return false;
    }
    
    return true;
}

std::vector<std::map<std::string, std::string>> Database::query(const std::string& sql) {
    std::vector<std::map<std::string, std::string>> results;
    
    sqlite3_stmt* stmt = prepare(sql);
    if (!stmt) {
        return results;
    }
    
    int columnCount = sqlite3_column_count(stmt);
    
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        std::map<std::string, std::string> row;
        
        for (int i = 0; i < columnCount; i++) {
            std::string columnName = sqlite3_column_name(stmt, i);
            const char* value = reinterpret_cast<const char*>(sqlite3_column_text(stmt, i));
            row[columnName] = value ? value : "";
        }
        
        results.push_back(row);
    }
    
    sqlite3_finalize(stmt);
    return results;
}

sqlite3_stmt* Database::prepare(const std::string& query) {
    sqlite3_stmt* stmt = nullptr;
    int result = sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr);
    
    if (result != SQLITE_OK) {
        lastError = sqlite3_errmsg(db);
        std::cerr << "Erreur préparation SQL: " << lastError << std::endl;
        return nullptr;
    }
    
    return stmt;
}

int Database::getLastInsertId() {
    return static_cast<int>(sqlite3_last_insert_rowid(db));
}

std::string Database::getLastError() const {
    return lastError;
}
