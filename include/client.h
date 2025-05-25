#ifndef CLIENT_H
#define CLIENT_H

#include "utilizator.h"
#include <iostream>

class Client : public Utilizator {
private:
	double bani = 0.0;
	unsigned int nrSedinte = 0;

public:
	explicit Client(const std::string& nume = "", const std::string& prenume = "",
					const std::string& email = "", const std::string& parola = "",
					unsigned int varsta = 0);

	Client(const std::string& nume, const std::string& prenume,
		   const std::string& email, const std::string& parola,
		   unsigned int varsta, double bani, unsigned int nrSedinte);

	Client(const Client& other);

	Client& operator=(const Client& other);

	Client& operator+=(double suma);

	~Client() override;

	double getBani() const;
	void adaugaBani(double suma);
	void scadeBani(double suma);
	unsigned int getNrSedinte() const;
	void adaugaSedinte(unsigned int nr);
	void scadeSedinta();

	void afiseazaProfil() const override;

	friend bool operator==(const Client& c1, const Client& c2);
};

#endif
