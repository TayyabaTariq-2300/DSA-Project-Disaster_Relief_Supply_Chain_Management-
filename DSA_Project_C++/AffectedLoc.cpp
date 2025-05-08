// AffectedLoc.cpp
#include "AffectedLoc.h"

AffectedLoc::AffectedLoc() : affectedPopPer(0), dead(0), injured(0), served(false), loc(nullptr), right(nullptr), left(nullptr) {}

AffectedLoc::AffectedLoc(Locations* l, std::string n, float affP, int d, int inj) : Locations(n), loc(l), affectedPopPer(affP), dead(d), injured(inj), served(false), right(nullptr), left(nullptr) {
    loc->setAffected(true);
}

void AffectedLoc::setSuplies(const Supplies& newSupplies) {
    supplies = newSupplies;
}

void AffectedLoc::displayNewSupplies() {
    supplies.displaySupplies();
}

bool AffectedLoc::isServed() {
    return served;
}

void AffectedLoc::markAsServed() {
    served = true;
}

void AffectedLoc::setRight(AffectedLoc* r) {
    right = r;
}

void AffectedLoc::setLeft(AffectedLoc* l) {
    left = l;
}

int AffectedLoc::getInjured() {
    return injured;
}

int AffectedLoc::getDead() {
    return dead;
}

int AffectedLoc::getAffectedPopPer() {
    return affectedPopPer;
}
AffectedLoc* AffectedLoc::getRight() {
    return right;
}

AffectedLoc* AffectedLoc::getLeft() {
    return left;
}

int AffectedLoc::getTotalPop() {
    return loc ? loc->getTotalPop() : 0;
}

void AffectedLoc::displayAffectedDetails() {
    loc->displayLocation();
    std::cout << "Affected Population Percentage: " << affectedPopPer << "%"
        << "\nDead People: " << dead
        << "\nInjured People: " << injured << std::endl;
}

Supplies AffectedLoc::getSupplies() const {
    return supplies;
}
