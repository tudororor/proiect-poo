#include "curs.h"

Curs::Curs(const std::string& stil, const std::string& zi, unsigned int ora,
		   unsigned int durata, unsigned int capacitate, const std::string& instructor,
		   unsigned int inscrisi)
	: stil(stil), ziSaptamana(zi), ora(ora), durataMinute(durata),
	  capacitateMaxima(capacitate), instructor(instructor),
	  persoaneInscrise(inscrisi) {}

Curs::~Curs() {}

std::ostream& operator<<(std::ostream& os, const Curs& curs) {
	os << "Stil: " << curs.stil << " | Zi: " << curs.ziSaptamana
	   << " | Ora: " << curs.ora << ":00 | Durata: " << curs.durataMinute << " min"
	   << " | Instructor: " << curs.instructor
	   << " | Capacitate: " << curs.capacitateMaxima;
	return os;
}

std::istream& operator>>(std::istream& is, Curs& curs) {
	std::cout << "Stil de dans: ";
	std::getline(is >> std::ws, curs.stil);

	std::cout << "Zi a saptamanii: ";
	std::getline(is >> std::ws, curs.ziSaptamana);

	std::cout << "Ora de incepere: ";
	is >> curs.ora;
	std::cout << "Durata (in minute): ";
	is >> curs.durataMinute;
	std::cout << "Capacitate maxima: ";
	is >> curs.capacitateMaxima;
	std::cout << "Instructor: ";
	std::getline(is >> std::ws, curs.instructor);

	return is;
}

std::string Curs::getStil() const {
	return stil;
}

std::string Curs::getZi() const {
	return ziSaptamana;
}

unsigned int Curs::getOra() const {
	return ora;
}

unsigned int Curs::getDurata() const {
	return durataMinute;
}

unsigned int Curs::getCapacitate() const {
	return capacitateMaxima;
}

std::string Curs::getInstructor() const {
	return instructor;
}

unsigned int Curs::getPersoaneInscrise() const {
	return persoaneInscrise;
}

void Curs::setPersoaneInscrise(unsigned int nr) {
	persoaneInscrise = nr;
}

void Curs::adaugaInscris() {
	if (persoaneInscrise < capacitateMaxima)
		++persoaneInscrise;
}

