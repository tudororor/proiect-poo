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

public:
	Curs(const std::string& stil = "", const std::string& ziSaptamana = "",
		 unsigned int ora = 0, unsigned int durataMinute = 0,
		 unsigned int capacitateMaxima = 0, const std::string& instructor = "");

	friend std::ostream& operator<<(std::ostream& os, const Curs& curs);
	friend std::istream& operator>>(std::istream& is, Curs& curs);

	~Curs();
};

#endif
