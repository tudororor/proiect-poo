#include "abonamentPremium.h"
#include <iostream>

AbonamentPremium::AbonamentPremium()
	: Abonament("Premium", 600, 20) {}

AbonamentPremium::~AbonamentPremium() = default;

void AbonamentPremium::afiseazaDetalii() const {
	std::cout << "Abonament PREMIUM - 600 lei/luna, 20 cursuri/luna, rezervari: max 4 ori pe sala/luna, "
			  << "20% discount la workshopuri." << std::endl;
}

bool AbonamentPremium::poateRezervaSala(const std::string& numeSala) {
	return rezervariPeSala[numeSala] < 4;
}

void AbonamentPremium::inregistreazaRezervare(const std::string& numeSala) {
	rezervariPeSala[numeSala]++;
}

unsigned int AbonamentPremium::getDiscountEvenimente() const {
	return 20;
}
