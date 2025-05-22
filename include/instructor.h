#ifndef INSTRUCTOR_H
#define INSTRUCTOR_H

#include "utilizator.h"
#include <iostream>

class Instructor : public Utilizator {
public:
	explicit Instructor(const std::string& nume = "", const std::string& prenume = "",
			   const std::string& email = "", const std::string& parola = "",
			   unsigned int varsta = 0);

	void afiseazaProfil() const override;

	~Instructor() override;
};

#endif