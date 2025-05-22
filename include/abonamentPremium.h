#ifndef ABONAMENTPREMIUM_H
#define ABONAMENTPREMIUM_H

#include "abonament.h"
#include <map>

class AbonamentPremium : public Abonament {
private:
	std::map<std::string, unsigned int> rezervariPeSala;

public:
	AbonamentPremium();
	~AbonamentPremium() override;

	void afiseazaDetalii() const override;

	bool poateRezervaSala(const std::string& numeSala);
	void inregistreazaRezervare(const std::string& numeSala);

	unsigned int getDiscountEvenimente() const;
};

#endif
