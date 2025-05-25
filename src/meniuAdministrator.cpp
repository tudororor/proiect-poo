#include "meniuAdministrator.h"

#include <algorithm>
#include <fstream>
#include <iostream>

#include "nlohmann/json.hpp"

#ifdef _WIN32
#define CLEAR "cls"
#else
#define CLEAR "clear"
#endif

MeniuAdministrator::MeniuAdministrator(std::vector<std::shared_ptr<Utilizator>>& utilizatori)
    : utilizatori(utilizatori) {}

void MeniuAdministrator::meniuAdministrator() {
    int optiune;
    do {
        system(CLEAR);
        std::cout << "--- MENIU ADMINISTRATOR ---\n\n";
        std::cout << "1. Afiseaza cont utilizator\n";
        std::cout << "2. Sterge cont utilizator\n";
        std::cout << "3. Delogare\n\n";
        std::cout << "Alege optiunea: ";
        std::cin >> optiune;

        switch (optiune) {
            case 1:
                afiseazaUtilizatorDetaliat(utilizatori);
                break;
            case 2:
                stergeUtilizator(utilizatori);
                break;
            case 3:
                std::cout << "Revenire la meniul principal.\n";
                break;
            default:
                std::cout << "Optiune invalida. Incearca din nou.\n";
        }

    } while (optiune != 3);
}

void MeniuAdministrator::afiseazaUtilizatorDetaliat(const std::vector<std::shared_ptr<Utilizator>>& utilizatori) {
    system(CLEAR);

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

void MeniuAdministrator::stergeUtilizator(std::vector<std::shared_ptr<Utilizator>>& utilizatori) {
    system(CLEAR);

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
    if (!f.is_open()) {
        std::cerr << "Eroare: nu pot deschide utilizatori.json pentru citire!\n";
        return;
    }

    nlohmann::json j;
    f >> j;
    f.close();

    nlohmann::json jNou = nlohmann::json::array();
    for (const auto& user : j) {
        if (user["email"] != email || user["parola"] != parola) {
            jNou.push_back(user);
        }
    }

    std::ofstream out("../utilizatori.json");
    if (!out.is_open()) {
        std::cerr << "Eroare: nu pot deschide utilizatori.json pentru scriere!\n";
        return;
    }

    out << std::setw(4) << jNou;
    out.close();

    std::cout << "Utilizatorul a fost sters cu succes.\n";
    std::cout << "\nApasa Enter pentru a continua...";
    std::cin.ignore();
    std::cin.get();
}