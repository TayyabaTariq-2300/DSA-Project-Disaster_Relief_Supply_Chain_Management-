#pragma once

#include <wx/wx.h>
#include "Locations.h"
#include "Supplies.h"
#include "BST.h"
#include "supplyQueue.h"
#include "Graph.h"
#include <vector>
class Graph;

class supplyLocations {
    Locations* loc;
    Supplies* items;
    BST* tree;
    supplyQueue queue;
    Graph* graph;


public:
    supplyLocations();
    supplyLocations(Locations* location, BST* sharedTree, Graph* g);
    void calculateItems(AffectedLoc* deletedAffLoc);
    void deliverSupplies(AffectedLoc* deletedAffLoc);
    void displaySupplyDetails();

    ; // Getter methods 
    Locations* getLocation() const;
    Supplies* getSupplies() const;
    Graph* getGraph() const;
};