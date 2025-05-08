#pragma once
#pragma once

#include "Locations.h"
#include "Supplies.h"

class AffectedLoc : public Locations {
    float affectedPopPer;
    int dead;
    int injured;
    bool served;
    AffectedLoc* right, * left;
    Supplies supplies;
    Locations* loc;
public:
    AffectedLoc();
    AffectedLoc(Locations* l, std::string n, float affP, int d, int inj);

    void setSuplies(const Supplies& newSupplies);
    void displayNewSupplies();
    bool isServed();
    void markAsServed();
    void setRight(AffectedLoc* r);
    void setLeft(AffectedLoc* l);
    int getInjured();
    int getDead();
    int getAffectedPopPer();
    AffectedLoc* getRight();
    AffectedLoc* getLeft();
    int getTotalPop();
    void displayAffectedDetails();
    Supplies getSupplies() const;
};