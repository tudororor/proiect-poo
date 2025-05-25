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
#include "instructorAdministrator.h"
#include "meniu.h"

int main() {
#ifdef CI_MODE
    std::cout << "[CI MODE] Executie scurta pentru GitHub Actions.\n";
    return 0;
#else
    Meniu m;
    m.ruleaza();
    return 0;
#endif
}

