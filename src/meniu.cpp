#include "../include/meniu.h"
#include <iostream>
#include <nlohmann/json.hpp>
#include <fstream>
#include <string>
#include <cstdlib>

using json = nlohmann::json;

void curataConsola() {
	system("cls");
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
		std::cout << "3. Sterge utilizator\n";
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
				std::cout << "\nApasa Enter pentru a te intoarce la meniul principal...";
				std::cin.get();
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

	json utilizatorNou = {
		{"nume", nume},
		{"prenume", prenume},
		{"email", email},
		{"parola", parola},
		{"varsta", varsta},
		{"tip", tipProfilText}
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
	std::cout << "Email: ";
	std::getline(std::cin >> std::ws, email);
	std::cout << "Parola: ";
	std::getline(std::cin >> std::ws, parola);

	std::ifstream in(path);
	if (!in.is_open()) {
		std::cerr << "Eroare: nu pot deschide utilizatori.json pentru citire!\n";
		return;
	}

	json j;
	in >> j;
	in.close();

	bool gasit = false;
	for (const auto& user : j) {
		if (user["email"] == email && user["parola"] == parola) {
			std::string nume = user["nume"];
			std::string prenume = user["prenume"];
			unsigned int varsta = user["varsta"];
			std::string tip = user["tip"];

			if (tip == "client") {
				utilizatorAutentificat = std::make_shared<Client>(nume, prenume, email, parola, varsta);
			} else if (tip == "instructor") {
				utilizatorAutentificat = std::make_shared<Instructor>(nume, prenume, email, parola, varsta);
			} else if (tip == "administrator") {
				utilizatorAutentificat = std::make_shared<Administrator>(nume, prenume, email, parola, varsta);
			} else if (tip == "instructor_administrator") {
				utilizatorAutentificat = std::make_shared<InstructorAdministrator>(nume, prenume, email, parola, varsta);
			} else {
				std::cerr << "Tip necunoscut de utilizator.\n";
				return;
			}

			std::cout << "Autentificare reusita. Bine ai revenit, " << prenume << "!\n";
			gasit = true;
			break;
		}
	}

	if (!gasit) {
		std::cout << "Email sau parola incorecta.\n";
	}
}

void Meniu::stergeUtilizator() {
	std::cout << "----- STERGE UTILIZATOR -----\n\n";

	std::string email, parola;
	std::cout << "Introdu emailul utilizatorului de sters: ";
	std::getline(std::cin >> std::ws, email);
	std::cout << "Introdu parola: ";
	std::getline(std::cin >> std::ws, parola);

	std::string path = "../utilizatori.json";
	json j;

	std::ifstream in(path);
	if (!in.is_open()) {
		std::cerr << "Eroare: nu pot deschide fisierul pentru citire.\n";
		return;
	}
	in >> j;
	in.close();

	bool gasit = false;
	json rezultatNou = json::array();

	for (const auto& user : j) {
		if (user["email"] == email && user["parola"] == parola) {
			gasit = true; // nu-l adăugăm în rezultatNou => va fi șters
		} else {
			rezultatNou.push_back(user);
		}
	}

	if (!gasit) {
		std::cout << "Email sau parola incorecta. Stergerea a fost anulata.\n";
		return;
	}

	std::ofstream out(path);
	if (!out.is_open()) {
		std::cerr << "Eroare: nu pot deschide fisierul pentru scriere.\n";
		return;
	}
	out << std::setw(4) << rezultatNou;
	out.close();

	std::cout << "Utilizator sters cu succes.\n";
}