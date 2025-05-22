#include "client.h"

Client::Client(const std::string& nume, const std::string& prenume,
			   const std::string& email, const std::string& parola,
			   unsigned int varsta)
	: Utilizator(nume, prenume, email, parola, varsta) {}

void Client::afiseazaProfil() const {
	std::cout << "Client: " << getNumeComplet() << ", " << getVarsta() << " ani\n";
}

Client::~Client() {
}