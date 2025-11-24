cmake_minimum_required(VERSION 3.10)
project(MainWindowApp)

set(CMAKE_CXX_STANDARD 17)

add_executable(MainWindowApp 
    main.cpp 
    MainWindow.cpp 
    Navigator.cpp
    Database.cpp
    ProfessionalType.cpp
    Patient.cpp
    HealthProfessional.cpp
    User.cpp
    AuthService.cpp
    MedicalRecord.cpp
    PatientDetailsWindow.cpp
    PatientCreateWindow.cpp
    LoginWindow.cpp
    UserManagementWindow.cpp
    UserCreateWindow.cpp
    UserDetailsWindow.cpp
    MedicalRecordWindow.cpp
)

# Lier SQLite3
target_link_libraries(MainWindowApp sqlite3)
