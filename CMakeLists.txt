cmake_minimum_required(VERSION 3.10)
project(MainWindowApp)

set(CMAKE_CXX_STANDARD 17)

# Include directories
include_directories(
    ${CMAKE_SOURCE_DIR}/include/models
    ${CMAKE_SOURCE_DIR}/include/windows
    ${CMAKE_SOURCE_DIR}/include/services
    ${CMAKE_SOURCE_DIR}/include/utils
)

# Source files
set(SOURCES
    main.cpp
    src/windows/MainWindow.cpp
    src/utils/Navigator.cpp
    src/utils/Database.cpp
    src/utils/ProfessionalType.cpp
    src/utils/AntecedentType.cpp
    src/utils/ConsultationStatus.cpp
    src/models/Patient.cpp
    src/models/HealthProfessional.cpp
    src/models/User.cpp
    src/models/MedicalRecord.cpp
    src/models/Antecedent.cpp
    src/models/Consultation.cpp
    src/models/Prescription.cpp
    src/models/Exam.cpp
    src/services/AuthService.cpp
    src/services/Statistics.cpp
    src/services/CSVExporter.cpp
    src/windows/PatientDetailsWindow.cpp
    src/windows/PatientCreateWindow.cpp
    src/windows/LoginWindow.cpp
    src/windows/UserManagementWindow.cpp
    src/windows/UserCreateWindow.cpp
    src/windows/UserDetailsWindow.cpp
    src/windows/MedicalRecordWindow.cpp
    src/windows/AntecedentWindow.cpp
    src/windows/ConsultationWindow.cpp
    src/windows/StatisticsWindow.cpp
    src/windows/ExportWindow.cpp
)

add_executable(MainWindowApp ${SOURCES})

# Lier SQLite3
target_link_libraries(MainWindowApp sqlite3)
