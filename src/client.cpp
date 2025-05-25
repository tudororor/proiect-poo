#include "client.h"
#include <iostream>

Client::Client(const std::string& nume, const std::string& prenume,
			   const std::string& email, const std::string& parola,
			   unsigned int varsta)
		: Utilizator(nume, prenume, email, parola, varsta) {}

Client::Client(const std::string& nume, const std::string& prenume,
			   const std::string& email, const std::string& parola,
			   unsigned int varsta, double bani, unsigned int nrSedinte)
		: Utilizator(nume, prenume, email, parola, varsta), bani(bani), nrSedinte(nrSedinte) {}

Client::Client(const Client& other)
		: Utilizator(other), bani(other.bani), nrSedinte(other.nrSedinte) {}

Client& Client::operator=(const Client& other) {
	if (this != &other) {
		Utilizator::operator=(other);
		bani = other.bani;
		nrSedinte = other.nrSedinte;
	}
	return *this;
}

Client& Client::operator+=(double suma) {
	bani += suma;
	return *this;
}

Client::~Client() = default;

double Client::getBani() const {
	return bani;
}

void Client::adaugaBani(double suma) {
	bani += suma;
}

void Client::scadeBani(double suma) {
	if (suma <= bani) bani -= suma;
}

unsigned int Client::getNrSedinte() const {
	return nrSedinte;
}

void Client::adaugaSedinte(unsigned int nr) {
	nrSedinte += nr;
}

void Client::scadeSedinta() {
	if (nrSedinte > 0) --nrSedinte;
}

void Client::afiseazaProfil() const {
	std::cout << "Client: " << getNumeComplet() << "\n"
			  << "Varsta: " << varsta << "\n"
			  << "Bani: " << bani << " lei\n"
			  << "Sedinte ramase: " << nrSedinte << "\n";
}

bool operator==(const Client& c1, const Client& c2) {
	return c1.email == c2.email;
}