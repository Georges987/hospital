# Système de Gestion Hospitalière

Un système complet de gestion d'informations médicales développé en C++17 avec SQLite3.

## 🏗️ Structure du Projet

```
cpp/
├── include/              # Fichiers d'en-tête (.h)
│   ├── models/          # Modèles de données
│   ├── windows/         # Interfaces utilisateur
│   ├── services/        # Services (Auth, Stats, Export)
│   └── utils/           # Utilitaires (DB, Navigation, Enums)
├── src/                 # Fichiers source (.cpp)
│   ├── models/          # Implémentations des modèles
│   ├── windows/         # Implémentations des fenêtres
│   ├── services/        # Implémentations des services
│   └── utils/           # Implémentations des utilitaires
├── build/               # Fichiers de compilation
├── main.cpp             # Point d'entrée de l'application
└── CMakeLists.txt       # Configuration CMake
```

## ✨ Fonctionnalités

### Gestion des Utilisateurs
- ✅ Authentification (login/logout)
- ✅ Rôles : Administrateur, Médecin, Secrétaire
- ✅ Permissions granulaires

### Gestion des Patients
- ✅ CRUD complet avec tous les attributs (date de naissance, sexe, groupe sanguin, etc.)
- ✅ Dossiers médicaux
- ✅ Antécédents médicaux (pathologies, chirurgies, allergies, traitements)
- ✅ Consultations (programmation, historique, complétion)
- ✅ Prescriptions médicales
- ✅ Examens médicaux

### Statistiques
- ✅ Dashboard complet pour administrateurs
- ✅ Métriques patients (total, par sexe, par âge)
- ✅ Métriques professionnels (par type, actifs)
- ✅ Métriques consultations (programmées, terminées, par période)
- ✅ Métriques antécédents

### Export de Données
- ✅ Export CSV des patients
- ✅ Export CSV des consultations
- ✅ Export CSV des statistiques

## 🚀 Compilation et Exécution

### Prérequis
- CMake 3.10+
- Compilateur C++17
- SQLite3

### Compilation

```bash
# Créer le dossier de build
mkdir -p build
cd build

# Générer les fichiers de build
cmake ..

# Compiler
make
```

### Exécution

```bash
# Depuis le dossier build
./MainWindowApp

# Ou depuis la racine
./build/MainWindowApp
```

### Identifiants par défaut

| Rôle | Utilisateur | Mot de passe |
|------|-------------|--------------|
| Administrateur | admin | admin123 |
| Médecin | doctor | doctor123 |
| Secrétaire | secretary | secretary123 |

## 📊 Architecture

### Modèles de Données (8)
- `Patient` - Informations patients
- `HealthProfessional` - Professionnels de santé
- `User` - Comptes utilisateurs
- `MedicalRecord` - Dossiers médicaux
- `Antecedent` - Antécédents médicaux
- `Consultation` - Consultations
- `Prescription` - Prescriptions
- `Exam` - Examens médicaux

### Services (3)
- `AuthService` - Authentification et permissions
- `Statistics` - Calcul des statistiques
- `CSVExporter` - Export de données

### Utilitaires (5)
- `Database` - Gestion SQLite (Singleton)
- `Navigator` - Navigation entre fenêtres
- `Window` - Classe de base pour les fenêtres
- `Model<T>` - ORM générique
- Enums : `ProfessionalType`, `AntecedentType`, `ConsultationStatus`

## 🗄️ Base de Données

Le système utilise SQLite3 avec 8 tables :
- `patients`
- `health_professionals`
- `users`
- `medical_records`
- `antecedents`
- `consultations`
- `prescriptions`
- `exams`

La base de données est créée automatiquement au premier lancement (`hospital.db`).

## 📝 Utilisation

### Workflow typique

1. **Connexion** : Utilisez les identifiants par défaut
2. **Gestion Patients** : Créer, consulter, modifier des patients
3. **Dossier Médical** : Accéder au dossier complet d'un patient
4. **Consultations** : Programmer et compléter des consultations
5. **Statistiques** (Admin) : Consulter le dashboard
6. **Export** (Admin) : Exporter les données en CSV

## 🛠️ Technologies

- **Langage** : C++17
- **Base de données** : SQLite3
- **Build** : CMake
- **Architecture** : MVC avec ORM custom
- **Patterns** : Singleton, Model-View

## 📦 Fichiers Exportés

Les exports CSV sont créés dans le répertoire courant :
- `patients_export.csv`
- `consultations_export.csv`
- `statistiques_export.csv`

## 🎯 Conformité

Ce projet implémente toutes les fonctionnalités requises :
- ✅ Gestion complète des patients
- ✅ Dossiers médicaux avec antécédents
- ✅ Système de consultations
- ✅ Statistiques et rapports
- ✅ Fonctionnalités bonus (prescriptions, examens, export CSV)

## 📄 Licence

Projet académique - Système de Gestion Hospitalière
