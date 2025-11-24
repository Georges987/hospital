# Hospital Management System

Application de gestion hospitalière avec architecture modulaire, système de navigation, et base de données SQLite.

## 🏗️ Architecture

Ce projet utilise une architecture scalable inspirée de Flutter et Laravel :

- **Window (abstraite)** : Interface pour toutes les fenêtres
- **Navigator** : Système de navigation par pile (push/pop)
- **ListWindow** : Composant générique réutilisable pour les listes
- **Database** : Singleton pour gérer SQLite
- **Model<T>** : ORM template pour les models (style Laravel)
- **Patient** : Model concret avec CRUD

## 📋 Prérequis

- CMake 3.10+
- Compilateur C++17 (g++, clang++)
- Make
- **SQLite3** : `sudo apt-get install libsqlite3-dev`

## 🚀 Compilation

```bash
# Créer le dossier build (si nécessaire)
mkdir -p build

# Compiler
cd build
cmake ..
make
```

## ▶️ Exécution

Depuis la racine du projet :

```bash
./build/MainWindowApp
```

Ou depuis le dossier build :

```bash
cd build
./MainWindowApp
```

## 📁 Structure du Projet

```
cpp/
├── Window.h                    # Classe abstraite de base
├── Navigator.h/cpp             # Système de navigation
├── ListWindow.h                # Composant liste générique
├── MainWindow.h/cpp            # Fenêtre principale
├── Database.h/cpp              # Singleton SQLite
├── Model.h                     # ORM template
├── Patient.h/cpp               # Model Patient
├── PatientDetailsWindow.h/cpp  # UI détails patient
├── main.cpp                    # Point d'entrée
├── CMakeLists.txt              # Configuration build
├── hospital.db                 # Base de données SQLite (auto-créée)
└── build/                      # Fichiers compilés
```

## 🎯 Utilisation

### Ajouter une Nouvelle Fenêtre

```cpp
class MyWindow : public Window {
    Navigator& navigator;
public:
    MyWindow(Navigator& nav) : navigator(nav) {}
    
    void show() override {
        std::cout << "Mon contenu" << std::endl;
    }
    
    bool handleInput() override {
        return true;  // false pour fermer
    }
    
    std::string getTitle() const override {
        return "Ma Fenêtre";
    }
};

// Utiliser
navigator.push(std::make_unique<MyWindow>(navigator));
```

### Créer un Nouveau Model

```cpp
class Doctor : public Model<Doctor> {
public:
    Doctor(const std::string& nom, const std::string& specialite);
    
    std::string getTableName() const override { return "doctors"; }
    std::map<std::string, std::string> toMap() const override;
    void fromMap(const std::map<std::string, std::string>& data) override;
    
private:
    std::string nom;
    std::string specialite;
};
```

### Utiliser l'ORM

```cpp
// Créer
Patient patient("Dupont", "Jean", 45, "0123456789");
patient.save();

// Lister
auto patients = Patient::all();

// Trouver
auto patient = Patient::find(1);

// Modifier
patient->setAge(46);
patient->save();

// Supprimer
patient->remove();
```

## 📚 Documentation

Voir [walkthrough.md](file:///home/alexis/.gemini/antigravity/brain/79d77d94-f36a-42d8-9abd-d166288fa7fe/walkthrough.md) pour des exemples détaillés et le guide complet.

## ✨ Fonctionnalités

- ✅ Navigation par pile (comme Flutter)
- ✅ Gestion automatique de la mémoire
- ✅ Composants réutilisables
- ✅ Architecture extensible
- ✅ Base de données SQLite
- ✅ ORM inspiré de Laravel
- ✅ CRUD complet pour les patients
- ✅ Interface de gestion des patients

## 🔮 Prochaines Étapes

- [ ] Ajouter d'autres models (Doctor, Appointment)
- [ ] Implémenter les relations entre models
- [ ] Ajouter un système de recherche
- [ ] Créer des rapports et statistiques
- [ ] Ajouter des tests unitaires
