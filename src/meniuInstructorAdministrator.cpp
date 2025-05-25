#include "meniuInstructorAdministrator.h"
#include <iostream>
#include <fstream>
#include <limits>
#include <algorithm>
#include <nlohmann/json.hpp>
#include "../include/utilitare.h"

using json = nlohmann::json;

MeniuInstructorAdministrator::MeniuInstructorAdministrator(std::shared_ptr<Utilizator> utilizator,
                                                           std::vector<std::shared_ptr<Utilizator>>& utilizatori)
    : utilizatorAutentificat(utilizator), utilizatori(utilizatori) {}

void MeniuInstructorAdministrator::meniuInstructorAdministrator() {
    int optiune;
    do {
        clearScreen();
        std::cout << "--- MENIU INSTRUCTOR + ADMIN ---\n\n";
        std::cout << "1. Creeaza curs\n";
        std::cout << "2. Sterge curs\n";
        std::cout << "3. Afiseaza cursuri proprii\n";
        std::cout << "4. Sterge propriul cont\n";
        std::cout << "5. Afiseaza cont utilizator\n";
        std::cout << "6. Sterge cont utilizator\n";
        std::cout << "7. Delogare\n\n";
        std::cout << "Alege optiunea: ";
        std::cin >> optiune;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        clearScreen();

        switch (optiune) {
            case 1: adaugaCurs(); break;
            case 2: stergeCurs(); break;
            case 3: afiseazaCursuriCreate(); break;
            case 4: stergeCont(); return;
            case 5: afiseazaUtilizatorDetaliat(); break;
            case 6: stergeAltUtilizator(); break;
            case 7:
                std::cout << "Delogare cu succes.\n";
                return;
            default:
                std::cout << "Optiune invalida.\n";
        }

        std::cout << "\nApasa ENTER pentru a continua...";
        std::cin.get();

    } while (true);
}

// ========== Instructor ==========

void MeniuInstructorAdministrator::adaugaCurs() {
    std::string stil, zi;
    unsigned int ora = 0, durata = 0, capacitate = 0;

    std::cout << "Introdu stilul de dans: ";
    std::getline(std::cin, stil);

    std::cout << "Introdu ziua saptamanii: ";
    std::getline(std::cin, zi);

    std::cout << "Introdu ora de incepere: ";
    while (!(std::cin >> ora) || ora > 23) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Ora invalida. Reintrodu (0-23): ";
    }

    std::cout << "Introdu durata (in minute): ";
    while (!(std::cin >> durata) || durata == 0) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Durata invalida. Reintrodu (> 0): ";
    }

    std::cout << "Introdu capacitatea maxima: ";
    while (!(std::cin >> capacitate) || capacitate == 0) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Capacitate invalida. Reintrodu (> 0): ";
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::string numeInstructor = utilizatorAutentificat->getNumeComplet();

    json j;
    std::ifstream in("../cursuri.json");
    if (in.is_open()) {
        try {
            in >> j;
            if (!j.is_array()) j = json::array();
        } catch (...) {
            j = json::array();
        }
        in.close();
    } else {
        j = json::array();
    }

    json cursJson = {
        {"stil", stil},
        {"ziSaptamana", zi},
        {"ora", ora},
        {"durataMinute", durata},
        {"capacitateMaxima", capacitate},
        {"instructor", numeInstructor},
        {"persoaneInscrise", 0}
    };

    j.push_back(cursJson);

    std::ofstream out("../cursuri.json");
    if (out.is_open()) {
        out << j.dump(4);
        out.close();
        std::cout << "\nCurs creat cu succes.\n";
    } else {
        std::cerr << "Eroare la deschiderea cursuri.json pentru scriere!\n";
    }
}

void MeniuInstructorAdministrator::afiseazaCursuriCreate() {
    json j;
    std::ifstream in("../cursuri.json");
    if (!in.is_open()) {
        std::cout << "Nu exista cursuri salvate.\n";
        return;
    }

    try {
        in >> j;
        in.close();
    } catch (...) {
        std::cout << "Eroare la citirea cursuri.json.\n";
        return;
    }

    std::string numeInstructor = utilizatorAutentificat->getNumeComplet();
    std::vector<json> cursuriInstructor;

    for (const auto& curs : j) {
        if (curs["instructor"] == numeInstructor) {
            cursuriInstructor.push_back(curs);
        }
    }

    if (cursuriInstructor.empty()) {
        std::cout << "Nu ai cursuri salvate in sistem.\n";
        return;
    }

    for (size_t i = 0; i < cursuriInstructor.size(); ++i) {
        std::cout << i + 1 << ". Stil: " << cursuriInstructor[i]["stil"]
                  << ", Zi: " << cursuriInstructor[i]["ziSaptamana"]
                  << ", Ora: " << cursuriInstructor[i]["ora"]
                  << ", Durata: " << cursuriInstructor[i]["durataMinute"]
                  << ", Capacitate: " << cursuriInstructor[i]["capacitateMaxima"] << "\n";
    }
}

void MeniuInstructorAdministrator::stergeCurs() {
    json j;
    std::ifstream in("../cursuri.json");
    if (!in.is_open()) {
        std::cerr << "Eroare: nu pot deschide cursuri.json pentru citire.\n";
        return;
    }
    in >> j;
    in.close();

    std::string numeInstructor = utilizatorAutentificat->getNumeComplet();
    std::vector<json> cursuriInstructor;

    for (const auto& curs : j) {
        if (curs["instructor"] == numeInstructor) {
            cursuriInstructor.push_back(curs);
        }
    }

    if (cursuriInstructor.empty()) {
        std::cout << "Nu exista cursuri de sters.\n";
        return;
    }

    for (size_t i = 0; i < cursuriInstructor.size(); ++i) {
        std::cout << i + 1 << ". Stil: " << cursuriInstructor[i]["stil"]
                  << ", Zi: " << cursuriInstructor[i]["ziSaptamana"]
                  << ", Ora: " << cursuriInstructor[i]["ora"]
                  << ", Durata: " << cursuriInstructor[i]["durataMinute"]
                  << ", Capacitate: " << cursuriInstructor[i]["capacitateMaxima"] << "\n";
    }

    std::cout << "\nIntrodu indexul cursului de sters: ";
    int index;
    std::cin >> index;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    if (index < 1 || static_cast<size_t>(index) > cursuriInstructor.size()) {
        std::cout << "Index invalid.\n";
        return;
    }

    char confirmare;
    std::cout << "Esti sigur ca vrei sa stergi cursul? (y/n): ";
    std::cin >> confirmare;
    std::cin.ignore();

    if (confirmare != 'y' && confirmare != 'Y') {
        std::cout << "Stergerea a fost anulata.\n";
        return;
    }

    json cursDeSters = cursuriInstructor[index - 1];
    json jNou = json::array();
    for (const auto& curs : j) {
        if (curs != cursDeSters)
            jNou.push_back(curs);
    }

    std::ofstream out("../cursuri.json");
    out << std::setw(4) << jNou;
    out.close();

    std::cout << "Curs sters cu succes.\n";
}

void MeniuInstructorAdministrator::stergeCont() {
    std::string email = utilizatorAutentificat->getEmail();

    std::cout << "Esti sigur ca vrei sa stergi contul tau? (y/n): ";
    char confirmare;
    std::cin >> confirmare;

    if (confirmare != 'y' && confirmare != 'Y') {
        std::cout << "Stergerea a fost anulata.\n";
        std::cout << "\nApasa ENTER pentru a reveni in meniu...";
        std::cin.ignore();
        std::cin.get();
        return;
    }

    // Sterge din vector
    auto it = std::remove_if(utilizatori.begin(), utilizatori.end(),
        [&](const std::shared_ptr<Utilizator>& u) {
            return u->getEmail() == email;
        });
    utilizatori.erase(it, utilizatori.end());

    // Stergere din utilizatori.json
    std::ifstream in("../utilizatori.json");
    json j;
    in >> j;
    in.close();

    json jNou = json::array();
    json utilizatorDeSters;

    for (const auto& user : j) {
        if (user["email"] != email)
            jNou.push_back(user);
        else
            utilizatorDeSters = user;
    }

    std::string numeComplet = utilizatorDeSters["prenume"].get<std::string>() + " " +
                              utilizatorDeSters["nume"].get<std::string>();

    std::ifstream inC("../cursuri.json");
    if (inC.is_open()) {
        json jCursuri;
        inC >> jCursuri;
        inC.close();

        json jNouCursuri = json::array();
        for (const auto& curs : jCursuri) {
            if (curs["instructor"] != numeComplet)
                jNouCursuri.push_back(curs);
        }

        std::ofstream outC("../cursuri.json");
        outC << std::setw(4) << jNouCursuri;
    }

    std::ofstream out("../utilizatori.json");
    out << std::setw(4) << jNou;
    out.close();

    std::cout << "Contul tau a fost sters cu succes.\n";
    std::cin.get();
}

// ========== Administrator ==========

void MeniuInstructorAdministrator::afiseazaUtilizatorDetaliat() {
    std::string email;
    std::cout << "Email: ";
    std::cin >> email;

    for (const auto& u : utilizatori) {
        if (u->getEmail() == email) {
            std::cout << "\nProfil gasit!\n";
            u->afiseazaProfil();

            std::cout << "\nApasa Enter pentru a continua...";
            std::cin.ignore();
            std::cin.get();
            return;
        }
    }

    std::cout << "Contul nu a fost gasit.\n";
    std::cout << "\nApasa Enter pentru a continua...";
    std::cin.ignore();
    std::cin.get();
}

void MeniuInstructorAdministrator::stergeAltUtilizator() {
    std::string email, parola;
    std::cout << "Email utilizator de sters: ";
    std::cin >> email;
    std::cout << "Parola: ";
    std::cin >> parola;

    auto it = std::find_if(utilizatori.begin(), utilizatori.end(),
        [&](const std::shared_ptr<Utilizator>& u) {
            return u->getEmail() == email && u->verificaParola(parola);
        });

    if (it == utilizatori.end()) {
        std::cout << "Email sau parola incorecta.\n";
        std::cout << "\nApasa Enter pentru a continua...";
        std::cin.ignore();
        std::cin.get();
        return;
    }

    char confirmare;
    std::cout << "Esti sigur ca vrei sa stergi utilizatorul? (y/n): ";
    std::cin >> confirmare;

    if (confirmare != 'y' && confirmare != 'Y') {
        std::cout << "Stergerea a fost anulata.\n";
        std::cout << "\nApasa Enter pentru a continua...";
        std::cin.ignore();
        std::cin.get();
        return;
    }

    utilizatori.erase(it);

    std::ifstream f("../utilizatori.json");
    json j;
    f >> j;
    f.close();

    json jNou = json::array();
    for (const auto& user : j) {
        if (user["email"] != email || user["parola"] != parola)
            jNou.push_back(user);
    }

    std::ofstream out("../utilizatori.json");
    out << std::setw(4) << jNou;
    out.close();

    std::cout << "Utilizatorul a fost sters cu succes.\n";
    std::cout << "\nApasa Enter pentru a continua...";
    std::cin.ignore();
    std::cin.get();
}
