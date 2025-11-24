#ifndef MODEL_H
#define MODEL_H

#include "Database.h"
#include <vector>
#include <map>
#include <string>
#include <sstream>
#include <memory>

template<typename T>
class Model {
public:
    virtual ~Model() = default;
    
    // CRUD statique
    static std::vector<T> all() {
        T temp;
        std::string tableName = temp.getTableName();
        std::string sql = "SELECT * FROM " + tableName;
        
        Database& db = Database::getInstance();
        auto results = db.query(sql);
        
        std::vector<T> models;
        for (const auto& row : results) {
            T model;
            model.fromMap(row);
            models.push_back(model);
        }
        
        return models;
    }
    
    static std::unique_ptr<T> find(int id) {
        T temp;
        std::string tableName = temp.getTableName();
        std::string sql = "SELECT * FROM " + tableName + " WHERE id = " + std::to_string(id);
        
        Database& db = Database::getInstance();
        auto results = db.query(sql);
        
        if (results.empty()) {
            return nullptr;
        }
        
        auto model = std::make_unique<T>();
        model->fromMap(results[0]);
        return model;
    }
    
    // CRUD d'instance
    virtual bool save() {
        Database& db = Database::getInstance();
        
        if (id == 0) {
            // INSERT
            auto data = toMap();
            std::string columns, values;
            
            for (const auto& [key, value] : data) {
                if (key == "id") continue;
                
                if (!columns.empty()) {
                    columns += ", ";
                    values += ", ";
                }
                columns += key;
                values += "'" + escapeString(value) + "'";
            }
            
            std::string sql = "INSERT INTO " + getTableName() + 
                            " (" + columns + ") VALUES (" + values + ")";
            
            if (db.execute(sql)) {
                id = db.getLastInsertId();
                return true;
            }
            return false;
        } else {
            // UPDATE
            auto data = toMap();
            std::string sets;
            
            for (const auto& [key, value] : data) {
                if (key == "id") continue;
                
                if (!sets.empty()) {
                    sets += ", ";
                }
                sets += key + " = '" + escapeString(value) + "'";
            }
            
            std::string sql = "UPDATE " + getTableName() + 
                            " SET " + sets + " WHERE id = " + std::to_string(id);
            
            return db.execute(sql);
        }
    }
    
    virtual bool remove() {
        if (id == 0) {
            return false;
        }
        
        Database& db = Database::getInstance();
        std::string sql = "DELETE FROM " + getTableName() + " WHERE id = " + std::to_string(id);
        
        bool success = db.execute(sql);
        if (success) {
            id = 0;
        }
        return success;
    }
    
    // Getters
    int getId() const { return id; }
    
protected:
    int id = 0;
    
    // Méthodes abstraites à implémenter
    virtual std::string getTableName() const = 0;
    virtual std::map<std::string, std::string> toMap() const = 0;
    virtual void fromMap(const std::map<std::string, std::string>& data) = 0;
    
    // Utilitaire pour échapper les chaînes SQL
    std::string escapeString(const std::string& str) const {
        std::string escaped;
        for (char c : str) {
            if (c == '\'') {
                escaped += "''";
            } else {
                escaped += c;
            }
        }
        return escaped;
    }
};

#endif // MODEL_H
