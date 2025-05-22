#include "administrator.h"

Administrator::Administrator(const std::string& nume, const std::string& prenume,
							 const std::string& email, const std::string& parola,
							 unsigned int varsta)
	: Utilizator(nume, prenume, email, parola, varsta) {}

void Administrator::afiseazaProfil() const {
	std::cout << "Administrator: " << getNumeComplet()
			  << ", " << getVarsta() << " ani" << std::endl;
}

Administrator::~Administrator() {
}
