#include "Supplies.h"
#include <iostream>

Supplies::Supplies() : food(500000), water(500000), clothes(500000), med(500000) {}

void Supplies::setFoodWaterClothes(int tp, int d) {
    food = tp - d;
    water = tp - d;
    clothes = tp - d;
}

void Supplies::updateFoodWaterClothes(int f, int w, int c) {
    std::cout << "\n inisde updatefWC.\n";
    food = (f < 0) ? 0 : f;
    water = (w < 0) ? 0 : w;
    clothes = (c < 0) ? 0 : c;
}
void Supplies::updateMed(int m) {
    med = (m < 0) ? 0 : m;
}


int Supplies::getFood() const{ return food; }

int Supplies::getWater() const{ return water; }

int Supplies::getClothes() const{ return clothes; }

void Supplies::setMed(int injured) {
    med = injured * 2;
}


int Supplies::getMed() const {
    return med;
}

void Supplies::displaySupplies() {
    std::cout << "\n=======Supply Items============\n";
    std::cout << "\nFood: " << food;
    std::cout << "\nWater: " << water;
    std::cout << "\nClothes: " << clothes;
    std::cout << "\nMedicines: " << med;
}
