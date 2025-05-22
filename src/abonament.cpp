#include "abonament.h"

// Constructor
Abonament::Abonament(const std::string& denumire, unsigned int pret, unsigned int numarCursuri)
	: denumire(denumire), pret(pret), numarCursuri(numarCursuri) {}

// Destructor
Abonament::~Abonament() = default;

// Getteri
std::string Abonament::getDenumire() const { return denumire; }
unsigned int Abonament::getPret() const { return pret; }
unsigned int Abonament::getNumarCursuri() const { return numarCursuri; }

// Setteri
void Abonament::setDenumire(const std::string& d) { denumire = d; }
void Abonament::setPret(unsigned int p) { pret = p; }
void Abonament::setNumarCursuri(unsigned int n) { numarCursuri = n; }

// Operator <<
std::ostream& operator<<(std::ostream& os, const Abonament& a) {
	os << "Abonament: " << a.denumire << " | Pret: " << a.pret
	   << " lei | Cursuri incluse: " << a.numarCursuri;
	return os;
}