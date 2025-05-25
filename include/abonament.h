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
	Abonament(const std::string& denumire = "", unsigned int pret = 0, unsigned int numarCursuri = 0);

	virtual ~Abonament();

	std::string getDenumire() const;
	unsigned int getPret() const;
	unsigned int getNumarCursuri() const;

	void setDenumire(const std::string& d);
	void setPret(unsigned int p);
	void setNumarCursuri(unsigned int n);

	virtual void afiseazaDetalii() const = 0;

	friend std::ostream& operator<<(std::ostream& os, const Abonament& a);
};

#endif