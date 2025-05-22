#include "abonamentStandard.h"
#include <iostream>

AbonamentStandard::AbonamentStandard()
	: Abonament("Standard", 200, 4) {}

AbonamentStandard::~AbonamentStandard() = default;

void AbonamentStandard::afiseazaDetalii() const {
	std::cout << "Abonament STANDARD - 200 lei/luna, include 4 cursuri." << std::endl;
}
