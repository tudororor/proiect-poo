#ifndef ABONAMENTPLUS_H
#define ABONAMENTPLUS_H

#include "abonament.h"
#include <map>

class AbonamentPlus : public Abonament {
private:
	std::map<std::string, unsigned int> rezervariPeSala;

public:
	AbonamentPlus();
	~AbonamentPlus() override;

	void afiseazaDetalii() const override;

	bool poateRezervaSala(const std::string& numeSala);
	void inregistreazaRezervare(const std::string& numeSala);
};

#endif