#pragma once
#pragma once

#include <string>
#include <iostream>
#include "Supplies.h"

class Supplies;
class Locations {
    std::string name;
    int totalPop;
    bool isAffected;
    Supplies originalSupplies;
public:
    Locations();
    Locations(std::string n, int tp);
    Locations(std::string n);

    void setAffected(bool status);
    bool getAffected() const;
    std::string getName() const;
    int getTotalPop();
    void displayLocation() const;
    Supplies& getOriginalSupplies();
};
