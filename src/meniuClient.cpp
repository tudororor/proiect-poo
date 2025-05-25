#include "../include/meniuClient.h"
#include "../include/rezervare.h"
#include "../include/client.h"
#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>
#include <limits>
#include <map>
#include <algorithm>

extern void clearScreen();

MeniuClient::MeniuClient(std::shared_ptr<Utilizator> utilizator)
    : utilizatorAutentificat(std::move(utilizator)) {}

void MeniuClient::meniuClient() {
    int optiune;

    do {
        clearScreen();
        std::cout << "----- MENIU CLIENT -----\n\n";
        std::cout << "1. Rezerva un curs\n";
        std::cout << "2. Vezi rezervarile\n";
        std::cout << "3. Anuleaza rezervare\n";
        std::cout << "4. Cumpara sedinte\n";
        std::cout << "5. Sterge contul meu\n";
        std::cout << "6. Delogare\n\n";
        std::cout << "Alege o optiune: ";
        std::cin >> optiune;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        clearScreen();

        if (optiune == 1) rezervaCurs();
        else if (optiune == 2) afiseazaRezervari();
        else if (optiune == 3) anuleazaRezervare();
        else if (optiune == 4) cumparaSedinte();
        else if (optiune == 5) {
            stergeCont();
            return;
        }
        else if (optiune == 6) {
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

void MeniuClient::rezervaCurs() {
    auto client = std::dynamic_pointer_cast<Client>(utilizatorAutentificat);
    if (!client) {
        std::cout << "Eroare: utilizatorul nu este client.\n";
        return;
    }

    if (client->getNrSedinte() == 0) {
        std::cout << "Nu ai suficiente sedinte disponibile. Cumpara mai intai.\n";
        return;
    }

    std::ifstream in("../cursuri.json");
    nlohmann::json j;
    in >> j;
    in.close();

    if (j.empty()) {
        std::cout << "Nu exista cursuri disponibile momentan.\n";
        return;
    }

    std::vector<nlohmann::json> cursuri(j.begin(), j.end());

    try {
        std::sort(cursuri.begin(), cursuri.end(), [](const auto& a, const auto& b) {
            static const std::map<std::string, int> ordineZile{
                {"Luni", 0}, {"Marti", 1}, {"Miercuri", 2},
                {"Joi", 3}, {"Vineri", 4}, {"Sambata", 5}, {"Duminica", 6}
            };

            int ziA = ordineZile.at(a.at("ziSaptamana"));
            int ziB = ordineZile.at(b.at("ziSaptamana"));

            if (ziA != ziB)
                return ziA < ziB;

            return a.at("ora").template get<int>() < b.at("ora").template get<int>();
        });
    } catch (const std::exception& e) {
        std::cout << "Eroare la sortarea cursurilor: " << e.what() << "\n";
        return;
    }

    std::cout << "----- CURSURI DISPONIBILE -----\n";
    std::cout << "Momentan ai in cont " << client->getNrSedinte() << " sedinte.\n\n";
    for (size_t i = 0; i < cursuri.size(); ++i) {
        const auto& c = cursuri[i];
        std::cout << i + 1 << ". " << c["stil"] << " cu " << c["instructor"]
                  << " | " << c["ziSaptamana"] << " la ora " << c["ora"]
                  << " (durata: " << c["durataMinute"] << " min)\n";
    }

    std::cout << "\nAlege cursul dorit (index): ";
    size_t index;
    std::cin >> index;

    if (index < 1 || index > cursuri.size()) {
        std::cout << "Index invalid.\n";
        return;
    }

    const auto& cursAles = cursuri[index - 1];

    std::ifstream rezervariIn("../rezervari.json");
    nlohmann::json jRez;
    if (rezervariIn.is_open()) {
        try {
            rezervariIn >> jRez;
        } catch (...) {
            jRez = nlohmann::json::array();
        }
        rezervariIn.close();
    }

    for (const auto& r : jRez) {
        if (r.contains("emailClient") &&
            r["emailClient"] == client->getEmail() &&
            r["stil"] == cursAles["stil"] &&
            r["zi"] == cursAles["ziSaptamana"] &&
            r["ora"] == cursAles["ora"] &&
            r["instructor"] == cursAles["instructor"]) {
            std::cout << "Ai deja o rezervare la acest curs!\n";
            std::cin.get();
            return;
        }
    }

    client->scadeSedinta();

    nlohmann::json rezervareNoua = {
        {"emailClient", client->getEmail()},
        {"tip", "curs"},
        {"stil", cursAles["stil"]},
        {"zi", cursAles["ziSaptamana"]},
        {"ora", cursAles["ora"]},
        {"instructor", cursAles["instructor"]}
    };

    jRez.push_back(rezervareNoua);

    std::ofstream rezervariOut("../rezervari.json");
    rezervariOut << std::setw(4) << jRez;
    rezervariOut.close();

    std::ifstream userIn("../utilizatori.json");
    nlohmann::json jUtil;
    userIn >> jUtil;
    userIn.close();

    for (auto& user : jUtil) {
        if (user["email"] == client->getEmail()) {
            user["nrSedinte"] = client->getNrSedinte();
        }
    }

    std::ofstream userOut("../utilizatori.json");
    userOut << std::setw(4) << jUtil;

    std::cout << "Rezervare efectuata cu succes!\n";
    std::cin.get();
}

void MeniuClient::afiseazaRezervari() {
    auto client = std::dynamic_pointer_cast<Client>(utilizatorAutentificat);
    if (!client) {
        std::cout << "Eroare: utilizatorul nu este client.\n";
        return;
    }

    std::ifstream in("../rezervari.json");
    nlohmann::json jRez;
    try {
        in >> jRez;
    } catch (...) {
        std::cout << "Eroare la citirea rezervarilor.\n";
        return;
    }
    in.close();

    std::vector<nlohmann::json> rezervariClient;
    for (const auto& r : jRez) {
        if (r.contains("emailClient") && r["emailClient"] == client->getEmail()) {
            rezervariClient.push_back(r);
        }
    }

    if (rezervariClient.empty()) {
        std::cout << "Nu ai rezervari active.\n";
        return;
    }

    std::map<std::string, int> zile = {
        {"Luni", 0}, {"Marti", 1}, {"Miercuri", 2},
        {"Joi", 3}, {"Vineri", 4}, {"Sambata", 5}, {"Duminica", 6}
    };

    std::sort(rezervariClient.begin(), rezervariClient.end(),
        [&zile](const auto& a, const auto& b) {
            int ziA = zile[a["zi"]];
            int ziB = zile[b["zi"]];
            if (ziA != ziB) return ziA < ziB;
            return a["ora"] < b["ora"];
        });

    std::cout << "----- REZERVARILE TALE -----\n\n";
    for (size_t i = 0; i < rezervariClient.size(); ++i) {
        const auto& r = rezervariClient[i];
        std::cout << i + 1 << ". " << r["stil"] << " cu " << r["instructor"]
                  << " | " << r["zi"] << " la ora " << r["ora"] << "\n";
    }
}

void MeniuClient::anuleazaRezervare() {
    auto client = std::dynamic_pointer_cast<Client>(utilizatorAutentificat);
    if (!client) {
        std::cout << "Eroare: utilizatorul nu este client.\n";
        return;
    }

    std::ifstream in("../rezervari.json");
    nlohmann::json jRez;
    try {
        in >> jRez;
    } catch (...) {
        std::cout << "Eroare la citirea rezervarilor.\n";
        return;
    }
    in.close();

    std::vector<nlohmann::json> rezervariClient;
    for (const auto& r : jRez) {
        if (r.contains("emailClient") && r["emailClient"] == client->getEmail()) {
            rezervariClient.push_back(r);
        }
    }

    if (rezervariClient.empty()) {
        std::cout << "Nu ai rezervari active.\n";
        return;
    }

    std::cout << "----- REZERVARILE TALE -----\n\n";
    for (size_t i = 0; i < rezervariClient.size(); ++i) {
        const auto& r = rezervariClient[i];
        std::cout << i + 1 << ". " << r["stil"] << " cu " << r["instructor"]
                  << " | " << r["zi"] << " la ora " << r["ora"] << "\n";
    }

    std::cout << "\nAlege rezervarea pe care vrei sa o anulezi (index): ";
    size_t index;
    std::cin >> index;

    if (index < 1 || index > rezervariClient.size()) {
        std::cout << "Index invalid.\n";
        return;
    }

    const auto& rezervareDeSters = rezervariClient[index - 1];
    auto it = std::remove_if(jRez.begin(), jRez.end(), [&](const auto& r) {
        return r == rezervareDeSters;
    });
    jRez.erase(it, jRez.end());

    std::ofstream out("../rezervari.json");
    out << std::setw(4) << jRez;
    out.close();

    client->adaugaSedinte(1);
    std::ifstream userIn("../utilizatori.json");
    nlohmann::json jUtil;
    userIn >> jUtil;
    userIn.close();

    for (auto& user : jUtil) {
        if (user["email"] == client->getEmail()) {
            user["nrSedinte"] = client->getNrSedinte();
        }
    }

    std::ofstream userOut("../utilizatori.json");
    userOut << std::setw(4) << jUtil;

    std::cout << "Rezervarea a fost anulata, iar sedinta a fost returnata.\n";
    std::cin.get();
}

void MeniuClient::cumparaSedinte() {
    auto client = std::dynamic_pointer_cast<Client>(utilizatorAutentificat);
    if (!client) {
        std::cout << "Eroare: utilizatorul nu este client.\n";
        return;
    }

    std::cout << "----- CUMPARA SEDINTE -----\n\n";
    std::cout << "Pretul unei sedinte este 30 lei, iar acum ai in cont " << client->getBani() << " lei.\n";
    std::cout << "Cate sedinte doresti sa cumperi? ";

    unsigned int nrSedinte = 0;
    std::cin >> nrSedinte;

    double costTotal = nrSedinte * 30.0;
    double baniDisponibili = client->getBani();

    if (baniDisponibili < costTotal) {
        std::cout << "Fonduri insuficiente! Ai doar " << baniDisponibili << " lei.\n";
        return;
    }

    client->scadeBani(costTotal);
    client->adaugaSedinte(nrSedinte);
    std::cout << "Ai cumparat cu succes " << nrSedinte << " sedinte. Iti mai raman " << client->getBani() << " lei.\n";
    std::cin.get();

    std::ifstream in("../utilizatori.json");
    nlohmann::json j;
    in >> j;
    in.close();

    for (auto& user : j) {
        if (user["email"] == client->getEmail()) {
            user["bani"] = client->getBani();
            user["nrSedinte"] = client->getNrSedinte();
        }
    }

    std::ofstream out("../utilizatori.json");
    out << std::setw(4) << j;
}

void MeniuClient::stergeCont() {
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
    for (const auto& user : j) {
        if (user["email"] != email) {
            jNou.push_back(user);
        }
    }

    std::ofstream out("../utilizatori.json");
    out << std::setw(4) << jNou;
    out.close();

    std::cout << "Contul tau a fost sters cu succes!\n";
    std::cin.ignore();
}
