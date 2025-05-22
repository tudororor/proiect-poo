#ifndef ABONAMENTSTANDARD_H
#define ABONAMENTSTANDARD_H

#include "abonament.h"

class AbonamentStandard : public Abonament {
public:
	AbonamentStandard();
	~AbonamentStandard() override;

	void afiseazaDetalii() const override;
};

#endif
