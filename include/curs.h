#ifndef CURS_H
#define CURS_H

#include <string>
#include <iostream>

class Curs {
private:
	std::string stil;
	std::string ziSaptamana;
	unsigned int ora;
	unsigned int durataMinute;
	unsigned int capacitateMaxima;
	std::string instructor;
	unsigned int persoaneInscrise;

public:
	std::string getStil() const;
	std::string getZi() const;
	unsigned int getOra() const;
	unsigned int getDurata() const;
	unsigned int getCapacitate() const;
	std::string getInstructor() const;
	unsigned int getPersoaneInscrise() const;
	void setPersoaneInscrise(unsigned int nr);
	void adaugaInscris(); // incrementează cu 1

	explicit Curs(const std::string& stil, const std::string& zi, unsigned int ora,
	 unsigned int durata, unsigned int capacitate, const std::string& instructor,
	 unsigned int inscrisi = 0);

	friend std::ostream& operator<<(std::ostream& os, const Curs& curs);
	friend std::istream& operator>>(std::istream& is, Curs& curs);

	~Curs();
};

#endif
