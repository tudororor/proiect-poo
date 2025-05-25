#include "meniu.h"

int main() {
#ifdef CI_MODE
    std::cout << "[CI MODE] Executie pentru a nu intra in infinite loop in Github Actions.\n";
    return 0;
#else
    Meniu m;
    m.meniuPrincipal();
    return 0;
#endif
}

