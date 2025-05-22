#include "instructorAdministrator.h"
#include <iostream>

InstructorAdministrator::InstructorAdministrator(const std::string& nume,
												 const std::string& prenume,
												 const std::string& email,
												 const std::string& parola,
												 unsigned int varsta)
	: Utilizator(nume, prenume, email, parola, varsta),
	  Instructor(nume, prenume, email, parola, varsta),
	  Administrator(nume, prenume, email, parola, varsta) {}

void InstructorAdministrator::afiseazaProfil() const {
	std::cout << "InstructorAdministrator: " << getNumeComplet() << ", Varsta: " << getVarsta() << "\n";
}
