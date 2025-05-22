#include <iostream>
#include "client.h"
#include "instructor.h"
#include "administrator.h"
#include "curs.h"
#include "sala.h"
#include "rezervare.h"
#include "abonamentStandard.h"
#include "abonamentPlus.h"
#include "abonamentPremium.h"

int main() {
    // Sala sala("Sala Mare", 70, 60, {
    //     {"Luni", {10, 11}}
    // });
    //
    // Rezervare<Sala> r(sala, "Luni", 10, "Gaozmin");
    //
    // r.afiseaza();
    //
    // Client c("X", "Y", "a@a.com", "123", 22);
    // c.afiseazaProfil();
    //
    // Instructor i("X", "Y", "a@a.com", "123", 22);
    // i.afiseazaProfil();
    //
    // Administrator a("X", "Y", "a@a.com", "123", 22);
    // a.afiseazaProfil();
    //
    // std::cout << "Numele salii: " << sala.getNume() << '\n';
    //
    // if (sala.esteLiberaLa("Luni", 10))
    //     std::cout << "Sala este libera Luni la 10\n";
    // else
    //     std::cout << "Sala este ocupata Luni la 10\n";
    //
    // sala.ocupaOra("Luni", 11);

    AbonamentStandard abs;
    abs.afiseazaDetalii();

    AbonamentPlus abp;
    abp.afiseazaDetalii();

    std::string sala = "Sala Mare";

    for (int i = 0; i < 3; ++i) {
        if (abp.poateRezervaSala(sala)) {
            std::cout << "Rezervare #" << i + 1 << " permisa\n";
            abp.inregistreazaRezervare(sala);
        } else {
            std::cout << "Rezervare #" << i + 1 << " REFUZATA pentru " << sala << "\n";
        }
    }

    AbonamentPremium apr;
    apr.afiseazaDetalii();

    std::string sala2 = "Sala Mica";

    for (int i = 1; i <= 5; ++i) {
        if (apr.poateRezervaSala(sala2)) {
            std::cout << "Rezervare #" << i << " permisa\n";
            apr.inregistreazaRezervare(sala2);
        } else {
            std::cout << "Rezervare #" << i << " REFUZATA pentru " << sala2 << "\n";
        }
    }

    std::cout << "Discount la evenimente: " << apr.getDiscountEvenimente() << "%\n";


    std::cout << "\nApasa Enter pentru a iesi...";
    std::cin.get();
    return 0;

}
