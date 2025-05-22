#include "abonamentPlus.h"
#include <iostream>

AbonamentPlus::AbonamentPlus()
	: Abonament("Plus", 450, 12) {}

AbonamentPlus::~AbonamentPlus() = default;

void AbonamentPlus::afiseazaDetalii() const {
	std::cout << "Abonament PLUS - 450 lei/luna, 12 cursuri/luna, rezervari: max 2 ori pe sala/luna." << std::endl;
}

bool AbonamentPlus::poateRezervaSala(const std::string& numeSala) {
	return rezervariPeSala[numeSala] < 2;
}

void AbonamentPlus::inregistreazaRezervare(const std::string& numeSala) {
	rezervariPeSala[numeSala]++;
}