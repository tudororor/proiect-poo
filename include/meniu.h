#ifndef MENIU_H
#define MENIU_H
#include <memory>
#include <vector>

#include "../include/utilizator.h"
#include "../include/client.h"
#include "../include/instructor.h"
#include "../include/administrator.h"
#include "../include/instructorAdministrator.h"

class Meniu {
private:
	std::vector<std::shared_ptr<Utilizator>> utilizatori;
	std::shared_ptr<Utilizator> utilizatorAutentificat;

public:
	std::shared_ptr<Utilizator> getUtilizatorAutentificat() const;

	Meniu();

	void ruleaza();

	void meniuPrincipal();

	void inregistrareUtilizator();

	void autentificareUtilizator();

	void delogare();

	void citesteUtilizatoriDinJson();

};

#endif
