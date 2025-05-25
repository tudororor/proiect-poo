#ifndef UTILITARE_H
#define UTILITARE_H

#ifdef _WIN32
#define CLEAR_COMMAND "cls"
#else
#define CLEAR_COMMAND "clear"
#endif

#include <cstdlib>

inline void clearScreen() {
	system(CLEAR_COMMAND);
}

#endif