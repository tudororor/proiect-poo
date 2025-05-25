#include "../include/meniuInstructor.h"
#include <iostream>
#include <limits>
#include <nlohmann/json.hpp>
#include <fstream>
#include "../include/utilitare.h"

MeniuInstructor::MeniuInstructor(std::shared_ptr<Utilizator> utilizator)
    : utilizatorAutentificat(std::move(utilizator)) {}

void MeniuInstructor::meniuInstructor() {
    int optiune;
    do {
        clearScreen();
        std::cout << "----- MENIU INSTRUCTOR -----\n\n";
        std::cout << "1. Creeaza curs\n";
        std::cout << "2. Sterge curs\n";
        std::cout << "3. Afiseaza cursuri\n";
        std::cout << "4. Sterge contul meu\n";
        std::cout << "5. Delogare\n\n";
        std::cout << "Alege o optiune: ";
        std::cin >> optiune;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        clearScreen();

        if (optiune == 1) adaugaCurs();
        else if (optiune == 2) stergeCurs();
        else if (optiune == 3) afiseazaCursuriCreate();
        else if (optiune == 4) {
            stergeCont();
            return;
        }
        else if (optiune == 5) {
            std::cout << "Delogare cu succes.\n";
            return;
        }
        else {
            std::cout << "Optiune invalida.\n";
        }

        std::cout << "\nApasa ENTER pentru a continua...";
        std::cin.get();

    } while (true);
}

void MeniuInstructor::adaugaCurs() {
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

    Curs nouCurs(stil, zi, ora, durata, capacitate, numeInstructor);
    cursuriCreate.push_back(nouCurs);

    nlohmann::json j;

    std::ifstream in("../cursuri.json");
    if (in.is_open()) {
        try {
            in >> j;
            if (!j.is_array()) j = nlohmann::json::array();
        } catch (...) {
            j = nlohmann::json::array();
        }
        in.close();
    } else {
        j = nlohmann::json::array();
    }

    nlohmann::json cursJson = {
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
    } else {
        std::cerr << "Eroare la deschiderea cursuri.json pentru scriere!\n";
    }

    std::cout << "\nCurs creat cu succes.\n";
}

void MeniuInstructor::afiseazaCursuriCreate() {
    nlohmann::json j;
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
    std::vector<nlohmann::json> cursuriInstructor;

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

void MeniuInstructor::stergeCurs() {
    nlohmann::json j;
    std::ifstream in("../cursuri.json");
    if (!in.is_open()) {
        std::cerr << "Eroare: nu pot deschide cursuri.json pentru citire.\n";
        return;
    }
    in >> j;
    in.close();

    std::string numeInstructor = utilizatorAutentificat->getNumeComplet();
    std::vector<nlohmann::json> cursuriInstructor;

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

    std::cout << "\nIntrodu indexul cursului pe care doriti sa il stergeti: ";
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

    nlohmann::json cursDeSters = cursuriInstructor[index - 1];

    nlohmann::json jNou = nlohmann::json::array();
    for (const auto& curs : j) {
        if (curs != cursDeSters) {
            jNou.push_back(curs);
        }
    }

    std::ofstream out("../cursuri.json");
    if (!out.is_open()) {
        std::cerr << "Eroare: nu pot deschide cursuri.json pentru scriere.\n";
        return;
    }
    out << std::setw(4) << jNou;
    out.close();

    std::cout << "Curs sters cu succes.\n";
}

void MeniuInstructor::stergeCont() {
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

    std::ifstream in("../utilizatori.json");
    if (!in.is_open()) {
        std::cerr << "Eroare la deschiderea utilizatori.json\n";
        return;
    }

    nlohmann::json j;
    in >> j;
    in.close();

    nlohmann::json jNou = nlohmann::json::array();
    nlohmann::json utilizatorDeSters;

    for (const auto& user : j) {
        if (user["email"] != email)
            jNou.push_back(user);
        else
            utilizatorDeSters = user;
    }

    std::ifstream inC("../cursuri.json");
    if (inC.is_open()) {
        nlohmann::json jCursuri;
        inC >> jCursuri;
        inC.close();

        std::string numeComplet = utilizatorDeSters["prenume"].get<std::string>() + " " +
                                  utilizatorDeSters["nume"].get<std::string>();

        nlohmann::json jNouCursuri = nlohmann::json::array();
        for (const auto& curs : jCursuri) {
            if (curs["instructor"] != numeComplet) {
                jNouCursuri.push_back(curs);
            }
        }

        std::ofstream outC("../cursuri.json");
        if (outC.is_open()) {
            outC << std::setw(4) << jNouCursuri;
            outC.close();
        }
    }

    std::ofstream out("../utilizatori.json");
    out << std::setw(4) << jNou;
    out.close();

    std::cout << "Contul tau a fost sters cu succes.\n";
    std::cin.get();
}