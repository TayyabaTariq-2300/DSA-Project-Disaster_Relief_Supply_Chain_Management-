#pragma once

#include<string>

#include "Locations.h"
#include "BST.h"
#include "supplyLocations.h"
#include "Supplies.h"
#include <wx/wx.h>

class supplyLocations;

using namespace std;

class Graph {
    Locations locations[10];
    int routes[10][10];
    BST* tree;
    supplyLocations* locs[3];
    Supplies* sup;
public:
    Graph() {}
    Graph(BST* sharedTree);
    Locations* getLocations();
    supplyLocations** getSupplyLocations();
    int minDistance(int dist[], bool sptSet[]);
    Locations* getLocationByName(const string& name);
    void handleSupplyChain(int totalAffected);
    void displayAllWarehouses();
    bool isValidName(const string& name);
    void displayLocations();
    void displayRoutes();
    void dijkstra(int src, int dist[], int prev[]);
    string getLocationName(int index);
    int getRoute(int from, int to);
};

