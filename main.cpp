#include <iostream>
#include "client.h"
#include "instructor.h"
#include "administrator.h"
#include "curs.h"
#include "sala.h"
#include "rezervare.h"

int main() {
    Sala sala("Sala Mare", 70, 60, {
        {"Luni", {10, 11}}
    });

    Rezervare<Sala> r(sala, "Luni", 10, "Gaozmin");

    // ✅ Apelăm afiseaza() — cppcheck nu va mai da warning
    r.afiseaza();

    Client c("X", "Y", "a@a.com", "123", 22);
    c.afiseazaProfil();

    Instructor i("X", "Y", "a@a.com", "123", 22);
    i.afiseazaProfil();

    Administrator a("X", "Y", "a@a.com", "123", 22);
    a.afiseazaProfil();

    std::cout << "Numele salii: " << sala.getNume() << '\n';

    if (sala.esteLiberaLa("Luni", 10))
        std::cout << "Sala este libera Luni la 10\n";
    else
        std::cout << "Sala este ocupata Luni la 10\n";

    sala.ocupaOra("Luni", 11);

    std::cout << "\nApasa Enter pentru a iesi...";
    std::cin.get();
    return 0;

}
