#include "../include/meniuClient.h"
#include "../include/rezervare.h"
#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>
#include <limits>
#include <map>
#include <algorithm>

#include "curs.h"

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
		std::cout << "4. Cumpara abonament\n";
		std::cout << "5. Delogare\n\n";
		std::cout << "Alege o optiune: ";
		std::cin >> optiune;
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

		clearScreen();

		if (optiune == 1) rezervaCurs();
		else if (optiune == 2) afiseazaRezervari();
		else if (optiune == 3) anuleazaRezervare();
		else if (optiune == 4) cumparaAbonament();
		else if (optiune == 5) {
			std::cout << "Delogare cu succes.\n";
			return;
		} else {
			std::cout << "Optiune invalida.\n";
		}

		std::cout << "\nApasa ENTER pentru a continua...";
		std::cin.get();

	} while (true);
}

void MeniuClient::rezervaCurs() {
    std::ifstream in("../cursuri.json");
    if (!in.is_open()) {
        std::cout << "Nu exista cursuri disponibile momentan.\n";
        return;
    }

    nlohmann::json j;
    try {
        in >> j;
        in.close();
    } catch (...) {
        std::cout << "Eroare la citirea cursuri.json.\n";
        return;
    }

    std::map<std::string, int> ziOrdine = {
        {"Luni", 1}, {"Marti", 2}, {"Miercuri", 3},
        {"Joi", 4}, {"Vineri", 5}, {"Sambata", 6}, {"Duminica", 7}
    };

    std::sort(j.begin(), j.end(), [&ziOrdine](const nlohmann::json& a, const nlohmann::json& b) {
        int ziA = ziOrdine[a["ziSaptamana"]];
        int ziB = ziOrdine[b["ziSaptamana"]];
        return (ziA == ziB) ? a["ora"] < b["ora"] : ziA < ziB;
    });

    std::cout << "Cursuri disponibile:\n";
    for (size_t i = 0; i < j.size(); ++i) {
        const auto& c = j[i];
        std::cout << i + 1 << ". Stil: " << c["stil"]
                  << ", Instructor: " << c["instructor"]
                  << ", Zi: " << c["ziSaptamana"]
                  << ", Ora: " << c["ora"]
                  << ", Durata: " << c["durataMinute"]
                  << ", Locuri: " << c["persoaneInscrise"] << "/" << c["capacitateMaxima"]
                  << "\n";
    }

    std::cout << "Introdu indexul cursului dorit: ";
    int index;
    std::cin >> index;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    if (index < 1 || static_cast<size_t>(index) > j.size()) {
        std::cout << "Index invalid.\n";
        return;
    }

    auto& cursJson = j[index - 1];

    if ((int)cursJson["persoaneInscrise"] >= (int)cursJson["capacitateMaxima"]) {
        std::cout << "Cursul este complet. Nu mai sunt locuri disponibile.\n";
        return;
    }

    if (utilizatorAutentificat->getNrSedinte() == 0) {
        std::cout << "Nu mai ai sedinte disponibile pe abonament.\n";
        return;
    }

    // Construim obiectul Curs din JSON
    Curs cursSelectat(
        cursJson["stil"],
        cursJson["ziSaptamana"],
        cursJson["ora"],
        cursJson["durataMinute"],
        cursJson["capacitateMaxima"],
        cursJson["instructor"]
    );

    // Cream o rezervare cu template
    Rezervare<Curs> rezervare(utilizatorAutentificat->getEmail(), cursSelectat);

    // Salvam rezervarea in JSON
    nlohmann::json rezervari;
    std::ifstream inRez("../rezervari.json");
    if (inRez.is_open()) {
        try {
            inRez >> rezervari;
        } catch (...) {
            rezervari = nlohmann::json::array();
        }
        inRez.close();
    } else {
        rezervari = nlohmann::json::array();
    }

    rezervari.push_back({
        {"emailClient", rezervare.getClient()},
        {"tip", "curs"},
        {"stil", cursSelectat.getStil()},
        {"zi", cursSelectat.getZi()},
        {"ora", cursSelectat.getOra()},
        {"instructor", cursSelectat.getInstructor()}
    });

    std::ofstream outRez("../rezervari.json");
    outRez << rezervari.dump(4);
    outRez.close();

    // Scadem o sedinta
    utilizatorAutentificat->scadeSedinta();

    // Actualizam persoaneInscrise
    cursJson["persoaneInscrise"] = (int)cursJson["persoaneInscrise"] + 1;
    std::ofstream out("../cursuri.json");
    out << j.dump(4);
    out.close();

    std::cout << "Rezervare efectuata cu succes.\n";
}

void MeniuClient::afiseazaRezervari() {
	std::cout << "Functia de afisare rezervari nu este inca implementata.\n";
}

void MeniuClient::anuleazaRezervare() {
	std::cout << "Functia de anulare rezervare nu este inca implementata.\n";
}

void MeniuClient::cumparaAbonament() {
	std::cout << "Functia de cumparare abonament nu este inca implementata.\n";
}
