#include "../include/meniu.h"
#include "../include/meniuInstructor.h"
#include "../include/meniuClient.h"
#include <iostream>
#include <nlohmann/json.hpp>
#include <fstream>
#include <string>
#include <cstdlib>

#include "meniuClient.h"

using json = nlohmann::json;

void curataConsola() {
#ifdef _WIN32
	system("cls");
#else
	system("clear");
#endif

}

Meniu::Meniu() = default;

void Meniu::ruleaza() {
	std::cout << "Bine ai venit la ~ Quest Dance Studio ~\n\n";
	std::cout << "Apasa Enter pentru a te duce la meniul principal...\n";
	std::cin.get();
	meniuPrincipal();
}

void Meniu::meniuPrincipal() {
	int optiune;
	do {
		curataConsola();

		std::cout << "----- MENIU PRINCIPAL -----\n\n";
		std::cout << "1. Inregistrare\n";
		std::cout << "2. Autentificare\n";
		std::cout << "3. Stergere cont\n";
		std::cout << "4. Iesire\n\n";
		std::cout << "Alege o optiune: ";
		std::cin >> optiune;

		switch (optiune) {
			case 1:
				curataConsola();
				inregistrareUtilizator();
				break;
			case 2:
				curataConsola();
				autentificareUtilizator();
				std::cout << "\nApasa Enter pentru a te intoarce la meniul principal...";
				std::cin.get();
				break;
			case 3:
				curataConsola();
				stergeUtilizator();
				break;
			case 4:
				std::cout << "La revedere!\n";
				break;
			default:
				std::cout << "Optiune invalida. Incearca din nou.\n";
		}
	} while (optiune != 4);

}

void Meniu::inregistrareUtilizator() {
	std::string path = "../utilizatori.json";
	std::string nume, prenume, email, parola;
	unsigned int varsta;

	std::cout << "----- INREGISTRARE -----\n\n";
	std::cout << "Nume: ";
	std::getline(std::cin >> std::ws, nume);
	std::cout << "Prenume: ";
	std::getline(std::cin >> std::ws, prenume);
	std::cout << "Email: ";
	std::getline(std::cin >> std::ws, email);
	std::cout << "Parola: ";
	std::getline(std::cin >> std::ws, parola);
	std::cout << "Varsta: ";
	std::cin >> varsta;

	double sumaInitiala;
	std::cout << "Introdu suma initiala din cont (lei): ";
	std::cin >> sumaInitiala;
	std::cin.ignore();

	auto client = std::make_shared<Client>(nume, prenume, email, parola, varsta);
	client->adaugaBani(sumaInitiala);

	int tipProfil = 0;
	std::string tipProfilText;

	do {
		std::cout << "\nAlege tipul de profil:\n";
		std::cout << "1. Client\n";
		std::cout << "2. Instructor\n";
		std::cout << "3. Administrator\n";
		std::cout << "4. InstructorAdministrator\n\n";
		std::cout << "Optiunea ta: ";
		std::cin >> tipProfil;

		switch (tipProfil) {
			case 1: tipProfilText = "client"; break;
			case 2: tipProfilText = "instructor"; break;
			case 3: tipProfilText = "administrator"; break;
			case 4: tipProfilText = "instructor_administrator"; break;
			default: std::cout << "Optiune invalida. Incearca din nou.\n";
		}
	} while (tipProfil < 1 || tipProfil > 4);

	json j;
	std::ifstream in(path);
	if (in.is_open()) {
		in >> j;
		in.close();
	}

	for (const auto& user : j) {
		if (user["email"] == email) {
			std::cout << "Exista deja un utilizator cu acest email!\n";
			std::cout << "\nApasa Enter pentru a te intoarce la meniul principal...";
			std::cin.get(); std::cin.get();
			return;
		}
	}

	nlohmann::json utilizatorNou = {
		{"tip", tipProfilText},
		{"email", email},
		{"parola", parola},
		{"nume", nume},
		{"prenume", prenume},
		{"varsta", varsta},
		{"bani", client->getBani()},
		{"nrSedinte", client->getNrSedinte()}
	};


	j.push_back(utilizatorNou);

	std::ofstream out(path);
	if (!out.is_open()) {
		std::cerr << "Eroare: nu pot deschide " << path << " pentru scriere!\n";
		std::cout << "\nApasa Enter pentru a te intoarce la meniul principal...";
		std::cin.get(); std::cin.get();
		return;
	}
	out << std::setw(4) << j;
	out.close();

	std::cout << "Utilizator inregistrat cu succes ca " << tipProfilText << "!\n";
	std::cout << "\nApasa Enter pentru a te intoarce la meniul principal...";
	std::cin.get(); std::cin.get();
}

void Meniu::autentificareUtilizator() {
    std::string path = "../utilizatori.json";

    std::cout << "----- AUTENTIFICARE -----\n\n";

    std::string email, parola;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // curățare buffer

    std::cout << "Email: ";
    std::getline(std::cin, email);

    std::cout << "Parola: ";
    std::getline(std::cin, parola);

    std::ifstream in(path);
    if (!in.is_open()) {
        std::cerr << "Eroare: nu pot deschide utilizatori.json pentru citire!\n";
        return;
    }

    nlohmann::json j;
    in >> j;

    for (const auto& utilizatorJson : j) {
        if (utilizatorJson["email"] == email && utilizatorJson["parola"] == parola) {
            std::string tip = utilizatorJson["tip"];
            std::string nume = utilizatorJson["nume"];
            std::string prenume = utilizatorJson["prenume"];

        	if (tip == "client") {
        		unsigned int varsta = utilizatorJson["varsta"];
        		double bani = utilizatorJson["bani"];

        		auto client = std::make_shared<Client>(nume, prenume, email, parola, varsta);
        		client->adaugaBani(bani);

        		utilizatorAutentificat = client;
        		MeniuClient meniu(client);
        		meniu.meniuClient();
        	}

        	else if (tip == "instructor") {
            	utilizatorAutentificat = std::make_shared<Instructor>(nume, prenume, email, parola);
            	MeniuInstructor meniu(utilizatorAutentificat);
            	meniu.meniuInstructor();
            }

            else if (tip == "administrator") {
                utilizatorAutentificat = std::make_shared<Administrator>(nume, prenume, email, parola);
                std::cout << "Autentificat ca administrator (meniu in lucru).\n";

            } else if (tip == "instructorAdministrator") {
                utilizatorAutentificat = std::make_shared<InstructorAdministrator>(nume, prenume, email, parola);
                std::cout << "Autentificat ca instructor+admin (meniu in lucru).\n";
            }

            return; // ieșire după autentificare reușită
        }
    }

    std::cout << "Email sau parola incorecte.\n";
}

void Meniu::stergeUtilizator() {
    std::cout << "----- STERGERE CONT -----\n\n";

    std::string email, parola;
    std::cout << "Introdu emailul contului de sters: ";
    std::getline(std::cin >> std::ws, email);
    std::cout << "Introdu parola: ";
    std::getline(std::cin >> std::ws, parola);

    std::string path = "../utilizatori.json";
    json j;

    std::ifstream in(path);
    if (!in.is_open()) {
        std::cerr << "Eroare: nu pot deschide fisierul pentru citire.\n";
        std::cout << "\nApasa Enter pentru a te intoarce la meniul principal...";
        std::cin.get();
        return;
    }
    in >> j;
    in.close();

    bool gasit = false;
    json rezultatNou = json::array();
    json utilizatorDeSters;

    for (const auto& user : j) {
        if (user["email"] == email && user["parola"] == parola) {
            gasit = true;
            utilizatorDeSters = user;
        } else {
            rezultatNou.push_back(user);
        }
    }

    if (!gasit) {
        std::cout << "Email sau parola incorecta. Stergerea a fost anulata.\n";
        std::cout << "\nApasa Enter pentru a te intoarce la meniul principal...";
        std::cin.get();
        return;
    }

    char confirmare;
    std::cout << "Esti sigur ca vrei sa stergi contul? (y/n): ";
    std::cin >> confirmare;
    std::cin.ignore();

    if (confirmare != 'y' && confirmare != 'Y') {
        std::cout << "Stergerea a fost anulata.\n";
        std::cout << "\nApasa Enter pentru a te intoarce la meniul principal...";
        std::cin.get();
        return;
    }

    // Dacă e instructor, ștergem și cursurile asociate lui
    if (utilizatorDeSters["tip"] == "instructor" || utilizatorDeSters["tip"] == "instructor_administrator") {
        std::ifstream fin("../cursuri.json");
        if (fin.is_open()) {
            json jCursuri;
            fin >> jCursuri;
            fin.close();

            std::string numeComplet = utilizatorDeSters["prenume"].get<std::string>() + " " +
                                      utilizatorDeSters["nume"].get<std::string>();

            json jNou = json::array();
            for (const auto& curs : jCursuri) {
                if (curs["instructor"] != numeComplet) {
                    jNou.push_back(curs);
                }
            }

            std::ofstream fout("../cursuri.json");
            if (fout.is_open()) {
                fout << std::setw(4) << jNou;
                fout.close();
            } else {
                std::cerr << "Eroare la scrierea in cursuri.json!\n";
            }
        }
    }

    // Suprascriem fisierul utilizatori.json fără utilizatorul de șters
    std::ofstream out(path);
    if (!out.is_open()) {
        std::cerr << "Eroare: nu pot deschide fisierul pentru scriere.\n";
        std::cout << "\nApasa Enter pentru a te intoarce la meniul principal...";
        std::cin.get();
        return;
    }
    out << std::setw(4) << rezultatNou;
    out.close();

    std::cout << "Utilizator sters cu succes.\n";
    std::cout << "\nApasa Enter pentru a te intoarce la meniul principal...";
    std::cin.get();
}


void Meniu::delogare() {
	utilizatorAutentificat = nullptr;
}

std::shared_ptr<Utilizator> Meniu::getUtilizatorAutentificat() const {
	return utilizatorAutentificat;
}