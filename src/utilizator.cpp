#include "utilizator.h"

Utilizator::Utilizator(const std::string& nume, const std::string& prenume,
					   const std::string& email, const std::string& parola,
					   unsigned int varsta)
	: nume(nume), prenume(prenume), email(email), parola(parola), varsta(varsta) {}

std::string Utilizator::getNumeComplet() const {
	return prenume + " " + nume;
}

unsigned int Utilizator::getVarsta() const {
	return varsta;
}

unsigned int Utilizator::getNrSedinte() const {
	return nrSedinte;
}

void Utilizator::scadeSedinta() {
	if (nrSedinte > 0) nrSedinte--;
}

std::string Utilizator::getEmail() const {
	return email;
}

Utilizator::~Utilizator() {
}

