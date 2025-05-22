#ifndef UTILIZATOR_H
#define UTILIZATOR_H

#include <string>

class Utilizator {
protected:
    std::string nume, prenume, email, parola;
    unsigned int varsta;

public:
    explicit Utilizator(const std::string& nume = "", const std::string& prenume = "",
               const std::string& email = "", const std::string& parola = "",
               unsigned int varsta = 0);

	virtual void afiseazaProfil() const = 0;

	std::string getNumeComplet() const;
	unsigned int getVarsta() const;

	virtual ~Utilizator() override;
};

#endif
