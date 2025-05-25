#ifndef MENIUINSTRUCTORADMINISTRATOR_H
#define MENIUINSTRUCTORADMINISTRATOR_H

#include "utilizator.h"
#include "curs.h"
#include <vector>
#include <memory>

class MeniuInstructorAdministrator {
private:
	std::shared_ptr<Utilizator> utilizatorAutentificat;
	std::vector<std::shared_ptr<Utilizator>>& utilizatori;

public:
	MeniuInstructorAdministrator(std::shared_ptr<Utilizator> utilizator,
								 std::vector<std::shared_ptr<Utilizator>>& utilizatori);

	void meniuInstructorAdministrator();

private:
	void adaugaCurs();
	void stergeCurs();
	void afiseazaCursuriCreate();
	void stergeCont();

	void afiseazaUtilizatorDetaliat();
	void stergeAltUtilizator();
};

#endif