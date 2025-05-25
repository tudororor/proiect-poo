#ifndef MENIUADMINISTRATOR_H
#define MENIUADMINISTRATOR_H

#include <vector>
#include <memory>
#include "utilizator.h"
#include "client.h"
#include "instructor.h"
#include "administrator.h"

class MeniuAdministrator {
private:
	std::vector<std::shared_ptr<Utilizator>>& utilizatori;

public:
	explicit MeniuAdministrator(std::vector<std::shared_ptr<Utilizator>>& utilizatori);

	void meniuAdministrator();

	static void afiseazaUtilizatorDetaliat(const std::vector<std::shared_ptr<Utilizator>>& utilizatori);
	static void stergeUtilizator(std::vector<std::shared_ptr<Utilizator>>& utilizatori);
};

#endif