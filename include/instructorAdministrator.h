#ifndef INSTRUCTORADMINISTRATOR_H
#define INSTRUCTORADMINISTRATOR_H

#include "instructor.h"
#include "administrator.h"

class InstructorAdministrator : public Instructor, public Administrator {
public:
	explicit InstructorAdministrator(const std::string& nume = "",
							const std::string& prenume = "",
							const std::string& email = "",
							const std::string& parola = "",
							unsigned int varsta = 0);

	void afiseazaProfil() const override;
};

#endif