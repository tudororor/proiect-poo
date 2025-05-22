#ifndef MENIU_H
#define MENIU_H
#include <memory>
#include "../include/utilizator.h"
#include "../include/client.h"
#include "../include/instructor.h"
#include "../include/administrator.h"
#include "../include/instructorAdministrator.h"

class Meniu {
private:
	std::shared_ptr<Utilizator> utilizatorAutentificat; // pointer inteligent către utilizatorul curent

public:
	Meniu();

	void ruleaza();

	void meniuPrincipal();

	void inregistrareUtilizator();

	void autentificareUtilizator();

	void stergeUtilizator();

};

#endif
