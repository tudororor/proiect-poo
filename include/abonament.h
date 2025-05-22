#ifndef ABONAMENT_H
#define ABONAMENT_H

#include <string>
#include <iostream>

class Abonament {
protected:
	std::string denumire;
	unsigned int pret;
	unsigned int numarCursuri;

public:
	// Constructor
	Abonament(const std::string& denumire = "", unsigned int pret = 0, unsigned int numarCursuri = 0);

	// Destructor virtual
	virtual ~Abonament();

	// Getteri
	std::string getDenumire() const;
	unsigned int getPret() const;
	unsigned int getNumarCursuri() const;

	// Setteri
	void setDenumire(const std::string& d);
	void setPret(unsigned int p);
	void setNumarCursuri(unsigned int n);

	// Funcție virtuală pură
	virtual void afiseazaDetalii() const = 0;

	// Operator <<
	friend std::ostream& operator<<(std::ostream& os, const Abonament& a);
};

#endif