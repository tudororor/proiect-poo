#ifndef SALA_H
#define SALA_H

#include <string>
#include <vector>
#include <map>
#include <iostream>

class Sala {
private:
	std::string nume;
	float metriPatrati;
	unsigned int pretRezervare;
	std::map<std::string, std::vector<unsigned int>> oreOcupate; // zi -> ore ocupate

public:
	explicit Sala(const std::string& nume = "", float metriPatrati = 0.0f,
		 unsigned int pretRezervare = 0,
		 const std::map<std::string, std::vector<unsigned int>>& oreOcupate = {});

	friend std::ostream& operator<<(std::ostream& os, const Sala& sala);
	friend std::istream& operator>>(std::istream& is, Sala& sala);

	const std::string& getNume() const { return nume; }

	bool esteLiberaLa(const std::string& zi, unsigned int ora) const;
	void ocupaOra(const std::string& zi, unsigned int ora);
};

#endif
