
// Locations.cpp
#include "Locations.h"

#include "Supplies.h"

class Supplies;

Locations::Locations() : name(" "), totalPop(0), isAffected(false), originalSupplies() {}

Locations::Locations(std::string n, int tp) : name(n), totalPop(tp), isAffected(false), originalSupplies() {}

Locations::Locations(std::string n) : name(n), totalPop(0), isAffected(false), originalSupplies() {}

void Locations::setAffected(bool status) {
    isAffected = status;
}

bool Locations::getAffected() const {
    return isAffected;
}

std::string Locations::getName() const {
    return name;
}

int Locations::getTotalPop() {
    return totalPop;
}

void Locations::displayLocation() const {
    std::cout << "\nLocation: " << name
        << "\n Total Population: " << totalPop
        << "\nAffected: " << (isAffected ? "Yes" : "No") << std::endl;
}

Supplies& Locations::getOriginalSupplies() {
    return originalSupplies;
}
