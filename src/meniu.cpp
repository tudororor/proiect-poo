#include "../include/meniu.h"
#include "../include/meniuInstructor.h"
#include "../include/meniuClient.h"
#include "../include/meniuAdministrator.h"
#include <iostream>
#include <nlohmann/json.hpp>
#include <fstream>
#include <string>
#include <cstdlib>
#include "client.h"
#include "instructor.h"
#include "administrator.h"
#include "meniuInstructorAdministrator.h"

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
	citesteUtilizatoriDinJson();
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
		std::cout << "3. Iesire\n\n";
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
				std::cout << "La revedere!\n";
				break;
			default:
				std::cout << "Optiune invalida. Incearca din nou.\n";
		}
	} while (optiune != 3);

}

void Meniu::inregistrareUtilizator() {
    std::string path = "../utilizatori.json";
    std::string nume, prenume, email, parola, inputVarsta, inputProfil;
    unsigned int varsta, tipProfil = 0;
    std::string tipProfilText;

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
    std::getline(std::cin, inputVarsta);
    while (!std::all_of(inputVarsta.begin(), inputVarsta.end(), ::isdigit) || inputVarsta.empty()) {
        std::cout << "Varsta invalida. Introdu o valoare numerica: ";
        std::getline(std::cin, inputVarsta);
    }
    varsta = static_cast<unsigned int>(std::stoi(inputVarsta));

    do {
        std::cout << "\nAlege tipul de profil:\n";
        std::cout << "1. Client\n";
        std::cout << "2. Instructor\n";
        std::cout << "3. Administrator\n";
        std::cout << "4. InstructorAdministrator\n\n";
        std::cout << "Optiunea ta: ";
        std::getline(std::cin, inputProfil);

        while (!std::all_of(inputProfil.begin(), inputProfil.end(), ::isdigit) || inputProfil.empty()) {
            std::cout << "Input invalid. Introdu un numar valid (1-4): ";
            std::getline(std::cin, inputProfil);
        }

        tipProfil = std::stoi(inputProfil);
        switch (tipProfil) {
            case 1: tipProfilText = "client"; break;
            case 2: tipProfilText = "instructor"; break;
            case 3: tipProfilText = "administrator"; break;
            case 4: tipProfilText = "instructor_administrator"; break;
            default: tipProfil = 0;
        }
        if (tipProfil == 0) std::cout << "Optiune invalida. Incearca din nou.\n";
    } while (tipProfil < 1 || tipProfil > 4);

    nlohmann::json j;
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

    nlohmann::json utilizatorNou;

    if (tipProfil == 1) {
        double sumaInitiala = 0;
        std::string inputSuma;
        std::cout << "Introdu suma initiala din cont (lei): ";
        std::getline(std::cin, inputSuma);
        while (true) {
            try {
                sumaInitiala = std::stod(inputSuma);
                if (sumaInitiala < 0) throw std::invalid_argument("negativ");
                break;
            } catch (...) {
                std::cout << "Suma invalida. Introdu un numar pozitiv: ";
                std::getline(std::cin, inputSuma);
            }
        }

        auto client = std::make_shared<Client>(nume, prenume, email, parola, varsta);
        client->adaugaBani(sumaInitiala);

        utilizatorNou = {
            {"tip", "client"},
            {"email", email},
            {"parola", parola},
            {"nume", nume},
            {"prenume", prenume},
            {"varsta", varsta},
            {"bani", client->getBani()},
            {"nrSedinte", client->getNrSedinte()}
        };
    } else {
        utilizatorNou = {
            {"tip", tipProfilText},
            {"email", email},
            {"parola", parola},
            {"nume", nume},
            {"prenume", prenume},
            {"varsta", varsta}
        };
    }

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
    std::cin.get();
}

void Meniu::autentificareUtilizator() {
    std::cout << "----- AUTENTIFICARE -----\n\n";

    std::string email, parola;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::cout << "Email: ";
    std::getline(std::cin, email);
    std::cout << "Parola: ";
    std::getline(std::cin, parola);

    std::ifstream in("../utilizatori.json");
    if (!in.is_open()) {
        std::cerr << "Eroare: nu pot deschide utilizatori.json pentru citire!\n";
        return;
    }

    json j;
    in >> j;

    for (const auto& user : j) {
        if (user["email"] == email && user["parola"] == parola) {
            std::string tip = user["tip"];
            std::string nume = user["nume"];
            std::string prenume = user["prenume"];
            unsigned int varsta = user["varsta"];

            if (tip == "client") {
                double bani = user["bani"];
                unsigned int nrSedinte = user["nrSedinte"];
                auto client = std::make_shared<Client>(nume, prenume, email, parola, varsta, bani, nrSedinte);
                utilizatorAutentificat = client;
                MeniuClient meniu(client);
                meniu.meniuClient();
            }

            else if (tip == "instructor") {
                auto instructor = std::make_shared<Instructor>(nume, prenume, email, parola, varsta);
                utilizatorAutentificat = instructor;
                MeniuInstructor meniu(instructor);
                meniu.meniuInstructor();
            }

            else if (tip == "administrator") {
                auto admin = std::make_shared<Administrator>(nume, prenume, email, parola, varsta);
                utilizatorAutentificat = admin;

                // reconstruim vectorul complet
                std::vector<std::shared_ptr<Utilizator>> utilizatoriLocal;
                for (const auto& item : j) {
                    std::string t = item.value("tip", "");
                    std::string n = item.value("nume", "");
                    std::string p = item.value("prenume", "");
                    std::string e = item.value("email", "");
                    std::string pw = item.value("parola", "");
                    unsigned int v = item.value("varsta", 0);

                    if (t == "client") {
                        double bani = item.value("bani", 0.0);
                        unsigned int sed = item.value("nrSedinte", 0);
                        utilizatoriLocal.push_back(std::make_shared<Client>(n, p, e, pw, v, bani, sed));
                    } else if (t == "instructor") {
                        utilizatoriLocal.push_back(std::make_shared<Instructor>(n, p, e, pw, v));
                    } else if (t == "administrator") {
                        utilizatoriLocal.push_back(std::make_shared<Administrator>(n, p, e, pw, v));
                    }
                }

                MeniuAdministrator meniu(utilizatoriLocal);
                meniu.meniuAdministrator();
            }

            else if (tip == "instructor_administrator") {
            	auto ia = std::make_shared<InstructorAdministrator>(nume, prenume, email, parola);
            	utilizatorAutentificat = ia;

            	// reconstruim vectorul complet
            	std::vector<std::shared_ptr<Utilizator>> utilizatoriLocal;
            	for (const auto& item : j) {
            		std::string t = item.value("tip", "");
            		std::string n = item.value("nume", "");
            		std::string p = item.value("prenume", "");
            		std::string e = item.value("email", "");
            		std::string pw = item.value("parola", "");
            		unsigned int v = item.value("varsta", 0);

            		if (t == "client") {
            			double bani = item.value("bani", 0.0);
            			unsigned int sed = item.value("nrSedinte", 0);
            			utilizatoriLocal.push_back(std::make_shared<Client>(n, p, e, pw, v, bani, sed));
            		} else if (t == "instructor") {
            			utilizatoriLocal.push_back(std::make_shared<Instructor>(n, p, e, pw, v));
            		} else if (t == "administrator") {
            			utilizatoriLocal.push_back(std::make_shared<Administrator>(n, p, e, pw, v));
            		} else if (t == "instructor_administrator") {
            			utilizatoriLocal.push_back(std::make_shared<InstructorAdministrator>(n, p, e, pw));
            		}
            	}

            	MeniuInstructorAdministrator meniu(ia, utilizatoriLocal);
            	meniu.meniuInstructorAdministrator();
            }

            return;
        }
    }

    std::cout << "Email sau parola incorecte.\n";
}


void Meniu::delogare() {
	utilizatorAutentificat = nullptr;
}

std::shared_ptr<Utilizator> Meniu::getUtilizatorAutentificat() const {
	return utilizatorAutentificat;
}

using json = nlohmann::json;

void Meniu::citesteUtilizatoriDinJson() {
	std::ifstream f("../utilizatori.json");
	if (!f.is_open()) {
		std::cerr << "Eroare: nu s-a putut deschide fisierul utilizatori.json\n";
		return;
	}

	json j;
	f >> j;

	for (const auto& item : j) {
		std::string tip = item.value("tip", "");
		std::string nume = item.value("nume", "");
		std::string prenume = item.value("prenume", "");
		std::string email = item.value("email", "");
		std::string parola = item.value("parola", "");
		unsigned int varsta = item.value("varsta", 0);

		if (tip == "client") {
			double bani = item.value("bani", 0.0);
			unsigned int nrSedinte = item.value("nrSedinte", 0);
			utilizatori.push_back(std::make_shared<Client>(nume, prenume, email, parola, varsta, bani, nrSedinte));
		} else if (tip == "instructor") {
			utilizatori.push_back(std::make_shared<Instructor>(nume, prenume, email, parola, varsta));
		} else if (tip == "administrator") {
			utilizatori.push_back(std::make_shared<Administrator>(nume, prenume, email, parola, varsta));
		}
		else if (tip == "instructor_administrator") {
			utilizatori.push_back(std::make_shared<InstructorAdministrator>(nume, prenume, email, parola));
		}
	}
}