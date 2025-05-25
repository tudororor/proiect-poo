#ifndef MENIUCLIENT_H
#define MENIUCLIENT_H

#include <memory>
#include "utilizator.h"

class MeniuClient {
private:
	std::shared_ptr<Utilizator> utilizatorAutentificat;

public:
	explicit MeniuClient(std::shared_ptr<Utilizator> utilizator);

	void meniuClient();

	void rezervaCurs();
	void afiseazaRezervari();
	void anuleazaRezervare();
	void cumparaSedinte();
	void stergeCont();

};

#endif
