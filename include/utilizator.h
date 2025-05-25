#ifndef UTILIZATOR_H
#define UTILIZATOR_H

#include <string>

class Utilizator {
protected:
    std::string nume, prenume, email, parola;
    unsigned int varsta, nrSedinte = 0;


public:
    Utilizator(const std::string& nume = "", const std::string& prenume = "",
               const std::string& email = "", const std::string& parola = "",
               unsigned int varsta = 0);

	virtual void afiseazaProfil() const = 0;
	bool verificaParola(const std::string& parolaIncercata) const {
		return parola == parolaIncercata;
	}

	std::string getNumeComplet() const;
	unsigned int getVarsta() const;

	unsigned int getNrSedinte() const;
	void scadeSedinta();
	std::string getEmail() const;

	virtual ~Utilizator();
};

#endif
