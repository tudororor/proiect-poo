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
    AbonamentStandard abs;
    abs.afiseazaDetalii();

    AbonamentPlus abp;
    abp.afiseazaDetalii();

    std::string sala = "Sala Mare";
    for (int i = 0; i < 3; ++i) {
        if (abp.poateRezervaSala(sala)) {
            std::cout << "Rezervare #" << i + 1 << " permisă\n";
            abp.inregistreazaRezervare(sala);
        } else {
            std::cout << "Rezervare #" << i + 1 << " REFUZATĂ pentru " << sala << "\n";
        }
    }

    AbonamentPremium apr;
    apr.afiseazaDetalii();

    std::string sala2 = "Sala Mica";
    for (int i = 1; i <= 5; ++i) {
        if (apr.poateRezervaSala(sala2)) {
            std::cout << "Rezervare #" << i << " permisă\n";
            apr.inregistreazaRezervare(sala2);
        } else {
            std::cout << "Rezervare #" << i << " REFUZATĂ pentru " << sala2 << "\n";
        }
    }

    std::cout << "Discount la evenimente: " << apr.getDiscountEvenimente() << "%\n";

    std::cout << "\nApasă Enter pentru a ieși...";
    std::cin.get();
    return 0;
}
