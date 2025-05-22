#ifndef CLIENT_H
#define CLIENT_H

#include "utilizator.h"
#include <iostream>

class Client : public Utilizator {
public:
	explicit Client(const std::string& nume = "", const std::string& prenume = "",
		   const std::string& email = "", const std::string& parola = "",
		   unsigned int varsta = 0);

	void afiseazaProfil() const override;

	~Client() override;
};

#endif
