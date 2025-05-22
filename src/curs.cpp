#include "curs.h"

Curs::Curs(const std::string& stil, const std::string& ziSaptamana,
		   unsigned int ora, unsigned int durataMinute,
		   unsigned int capacitateMaxima, const std::string& instructor)
	: stil(stil), ziSaptamana(ziSaptamana), ora(ora),
	  durataMinute(durataMinute), capacitateMaxima(capacitateMaxima),
	  instructor(instructor) {}

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
