#ifndef MENIUINSTRUCTOR_H
#define MENIUINSTRUCTOR_H

#include "utilizator.h"
#include "curs.h"
#include <memory>
#include <vector>

class MeniuInstructor {
private:
	std::shared_ptr<Utilizator> utilizatorAutentificat;
	std::vector<Curs> cursuriCreate;

public:
	explicit MeniuInstructor(std::shared_ptr<Utilizator> utilizator);

	void meniuInstructor();

	void adaugaCurs();

	void afiseazaCursuriCreate();

	void stergeCurs();

};

#endif
