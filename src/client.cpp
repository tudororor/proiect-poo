#include "client.h"

Client::Client(const std::string& nume, const std::string& prenume,
			   const std::string& email, const std::string& parola,
			   unsigned int varsta)
	: Utilizator(nume, prenume, email, parola, varsta) {}

void Client::afiseazaProfil() const {
	std::cout << "Client: " << getNumeComplet() << ", " << getVarsta() << " ani\n";
}

double Client::getBani() const {
	return bani;
}

void Client::adaugaBani(double suma) {
	bani += suma;
}

bool Client::scadeBani(double suma) {
	if (bani >= suma) {
		bani -= suma;
		return true;
	}
	return false;
}

Client::~Client() {
}