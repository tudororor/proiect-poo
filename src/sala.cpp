#include "sala.h"
#include <algorithm>

Sala::Sala(const std::string& nume, float metriPatrati, unsigned int pretRezervare,
           const std::map<std::string, std::vector<unsigned int>>& oreOcupate)
    : nume(nume), metriPatrati(metriPatrati),
      pretRezervare(pretRezervare), oreOcupate(oreOcupate) {}

std::ostream& operator<<(std::ostream& os, const Sala& sala) {
    os << "Sala: " << sala.nume
       << " | Suprafata: " << sala.metriPatrati << " mp"
       << " | Pret/ora: " << sala.pretRezervare << " lei"
       << " | Ore ocupate: ";
    for (const auto& pereche : sala.oreOcupate) {
        os << pereche.first << ": ";
        for (auto ora : pereche.second) {
            os << ora << ":00 ";
        }
        os << "| ";
    }
    return os;
}

std::istream& operator>>(std::istream& is, Sala& sala) {
    std::cout << "Nume sala: ";
    std::getline(is >> std::ws, sala.nume);
    std::cout << "Suprafata (mp): ";
    is >> sala.metriPatrati;
    std::cout << "Pret rezervare (lei/ora): ";
    is >> sala.pretRezervare;

    sala.oreOcupate.clear();
    std::cout << "Cate zile au ore ocupate?: ";
    int nrZile;
    is >> nrZile;

    for (int i = 0; i < nrZile; ++i) {
        std::string zi;
        int nrOre;
        std::cout << "Zi #" << (i + 1) << ": ";
        std::getline(is >> std::ws, zi);
        std::cout << "Cate ore ocupate in " << zi << "?: ";
        is >> nrOre;

        std::vector<unsigned int> ore;
        std::cout << "Introdu orele (ex: 10 pentru 10:00): ";
        for (int j = 0; j < nrOre; ++j) {
            unsigned int ora;
            is >> ora;
            ore.push_back(ora);
        }

        sala.oreOcupate[zi] = ore;
    }

    return is;
}

bool Sala::esteLiberaLa(const std::string& zi, unsigned int ora) const {
    auto it = oreOcupate.find(zi);
    if (it == oreOcupate.end()) return true;
    return std::find(it->second.begin(), it->second.end(), ora) == it->second.end();
}

void Sala::ocupaOra(const std::string& zi, unsigned int ora) {
    oreOcupate[zi].push_back(ora);
}
