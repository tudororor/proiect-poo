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
    // Testare clase de utilizatori
    Client c("Gaozmin", "Popescu", "gaozmin@studio.com", "parola123", 25);
    c.afiseazaProfil();

    Instructor i("Ana", "Ionescu", "ana@studio.com", "parola456", 30);
    i.afiseazaProfil();

    Administrator a("Radu", "Stan", "radu@studio.com", "adminpass", 40);
    a.afiseazaProfil();

    // Testare sala
    Sala s("Sala Mare", 70, 60, { {"Luni", {10, 12}} });
    std::cout << "Numele salii: " << s.getNume() << '\n';

    if (s.esteLiberaLa("Luni", 11)) {
        std::cout << "Sala este libera la 11\n";
    } else {
        std::cout << "Sala este ocupata la 11\n";
    }

    s.ocupaOra("Luni", 11); // ora 11 devine ocupata

    // Testare rezervare
    Rezervare<Sala> rez(s, "Luni", 12, "Popescu Gaozmin");
    rez.afiseaza();

    // Testare abonamente
    AbonamentStandard ab1;
    ab1.afiseazaDetalii();
    std::cout << ab1.getDenumire() << " - " << ab1.getPret() << " RON - " << ab1.getNumarCursuri() << " cursuri\n";
    ab1.setDenumire("Standard+");
    ab1.setPret(210);
    ab1.setNumarCursuri(5);

    AbonamentPlus abp;
    abp.afiseazaDetalii();
    for (int i = 0; i < 3; ++i) {
        if (abp.poateRezervaSala("Sala Mare")) {
            std::cout << "Rezervare #" << i + 1 << " permisa\n";
            abp.inregistreazaRezervare("Sala Mare");
        } else {
            std::cout << "Rezervare #" << i + 1 << " REFUZATA\n";
        }
    }

    AbonamentPremium abpr;
    abpr.afiseazaDetalii();
    for (int i = 0; i < 5; ++i) {
        if (abpr.poateRezervaSala("Sala Mica")) {
            std::cout << "Rezervare Premium #" << i + 1 << " permisa\n";
            abpr.inregistreazaRezervare("Sala Mica");
        } else {
            std::cout << "Rezervare Premium #" << i + 1 << " REFUZATA\n";
        }
    }
    std::cout << "Discount abonament premium: " << abpr.getDiscountEvenimente() << "%\n";

    std::cout << "\nApasa Enter pentru a iesi...";
    std::cin.get();
    return 0;
}
