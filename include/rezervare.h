#ifndef REZERVARE_H
#define REZERVARE_H

#include <iostream>
#include <string>

template <typename T>
class Rezervare {
private:
	T obiect;
	std::string zi;
	unsigned int ora;
	std::string numeClient;

public:
	// Constructor detaliat
	Rezervare(const T& obiect, const std::string& zi, unsigned int ora, const std::string& numeClient)
		: obiect(obiect), zi(zi), ora(ora), numeClient(numeClient) {}

	// Constructor simplificat (folosit în meniuClient)
	Rezervare(const std::string& numeClient, const T& obiect)
		: obiect(obiect), numeClient(numeClient) {
		zi = obiect.getZi();
		ora = obiect.getOra();
	}

	std::string getClient() const {
		return numeClient;
	}

	void afiseaza() const {
		std::cout << "Rezervare pentru: " << numeClient << "\n";
		std::cout << "Zi: " << zi << ", ora: " << ora << ":00\n";
		std::cout << "Obiect rezervat:\n" << obiect << "\n";
	}
};

#endif