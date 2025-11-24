#ifndef PERSON_H
#define PERSON_H

#include <string>

class Person {
public:
    virtual ~Person() = default;
    
    // Getters communs (id vient de Model)
    std::string getNom() const { return nom; }
    std::string getPrenom() const { return prenom; }
    std::string getTelephone() const { return telephone; }
    std::string getFullName() const { return prenom + " " + nom; }
    
    // Setters
    void setNom(const std::string& n) { nom = n; }
    void setPrenom(const std::string& p) { prenom = p; }
    void setTelephone(const std::string& t) { telephone = t; }
    
protected:
    std::string nom;
    std::string prenom;
    std::string telephone;
};

#endif // PERSON_H
