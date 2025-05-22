#ifndef ADMINISTRATOR_H
#define ADMINISTRATOR_H

#include "utilizator.h"
#include <iostream>

class Administrator : virtual public Utilizator {
public:
	explicit Administrator(const std::string& nume = "", const std::string& prenume = "",
				  const std::string& email = "", const std::string& parola = "",
				  unsigned int varsta = 0);

	void afiseazaProfil() const override;

	~Administrator() override;
};

#endif