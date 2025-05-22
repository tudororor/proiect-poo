#include "instructor.h"

Instructor::Instructor(const std::string& nume, const std::string& prenume,
					   const std::string& email, const std::string& parola,
					   unsigned int varsta)
	: Utilizator(nume, prenume, email, parola, varsta) {}

void Instructor::afiseazaProfil() const {
	std::cout << "Instructor: " << getNumeComplet()
			  << ", " << getVarsta() << " ani" << std::endl;
}

Instructor::~Instructor() {
}
