// supplyLocations.cpp
#include "supplyLocations.h"
#include "Graph.h"
#include <iostream>
#include <vector>
#include "MyFrame.h"
#include <wx/wx.h>


using namespace std;

supplyLocations::supplyLocations() : loc(nullptr), items(new Supplies()), tree(nullptr), graph(new Graph()) {}

supplyLocations::supplyLocations(Locations* location, BST* sharedTree, Graph* g) : loc(location), tree(sharedTree), items(new Supplies()), graph(g) {}


void supplyLocations::calculateItems(AffectedLoc* deletedAffLoc) {
    if (deletedAffLoc == nullptr) {
        std::cout << "\ninside calculate items of supplyLocations..";
        std::cout << "\n The tree is empty.\n";
        return;
    }

    int inj = deletedAffLoc->getInjured();
    int totalPop = deletedAffLoc->getTotalPop();
    int dead = deletedAffLoc->getDead();

    std::cout << " Total Population: " << totalPop << " \n Dead: " << dead << std::endl;
    items->setFoodWaterClothes(totalPop, dead);
    items->setMed(inj);

    queue.enqueue(*items);
}


void supplyLocations::deliverSupplies(AffectedLoc* deletedAffLoc) {

    if (deletedAffLoc == nullptr) {
        cout << "\nNo more locations to deliver supplies.\n";
        return;
    }
    int nearestWarehouseIndex = -1;
    int dist[10];
    int prev[10];
    int affectedIndex = -1;

    // Find the index of the affected location in the locations array
    Locations* locations = graph->getLocations();
    for (int i = 0; i < 10; i++) {
        if (locations[i].getName() == deletedAffLoc->getName()) {
            affectedIndex = i;

            break;
        }
    }

    if (affectedIndex == -1) {
        cout << "\nAffected location not found in the graph.\n";
        return;
    }

    // Run Dijkstra's algorithm from the affected location
    graph->dijkstra(affectedIndex, dist, prev);


    int minDistance = INT_MAX;
    supplyLocations** locs = graph->getSupplyLocations();
    for (int i = 0; i < 3; i++) {
        int warehouseIndex = -1;
        for (int j = 0; j < 10; j++) {
            if (locations[j].getName() == locs[i]->loc->getName()) {
                warehouseIndex = j;
                break;
            }
        }
        if (warehouseIndex != -1 && dist[warehouseIndex] < minDistance) {
            minDistance = dist[warehouseIndex];
            nearestWarehouseIndex = warehouseIndex;

        }
    }

    if (nearestWarehouseIndex == -1) {
        cout << "\nNo warehouse found for the affected location.\n";
        return;
    }

   
    // Display the path
    cout << "Path: ";
    int current = nearestWarehouseIndex;
    while (current != affectedIndex) {
        cout << locations[current].getName() << " <- ";
        current = prev[current];
    }
    cout << locations[affectedIndex].getName() << "\n";


    // Deliver supplies from the nearest warehouse


    int i = 0;
    while (!queue.isEmpty()) {
     Supplies s = queue.dequeue();
        deletedAffLoc->setSuplies(s);
        wxLogMessage("n===============Delivering supplies to deletedAffLoc->getName() with the following details:================\n");
        deletedAffLoc->displayNewSupplies();

        //supplyLocations** suppLoc = locations[nearestWarehouseIndex];

        cout << "\n locations[nearestWarehouseIndex].getOriginalSupplies().getFood() - s.getFood()" << locations[nearestWarehouseIndex].getOriginalSupplies().getFood() - s.getFood();
        locations[nearestWarehouseIndex].getOriginalSupplies().updateFoodWaterClothes(locations[nearestWarehouseIndex].getOriginalSupplies().getFood() - s.getFood(),
            locations[nearestWarehouseIndex].getOriginalSupplies().getWater() - s.getWater(),
            locations[nearestWarehouseIndex].getOriginalSupplies().getClothes() - s.getClothes()
        );
        locations[nearestWarehouseIndex].getOriginalSupplies().updateMed(locations[nearestWarehouseIndex].getOriginalSupplies().getMed() - s.getMed());
       
        locations[nearestWarehouseIndex].getOriginalSupplies().displaySupplies();

      

    }

}

void supplyLocations::displaySupplyDetails() {
    std::cout << loc->getName();
    items->displaySupplies();
}


// Getter methods 
Locations* supplyLocations::getLocation() const { return loc; }
Supplies* supplyLocations::getSupplies() const { return items; }
Graph* supplyLocations::getGraph() const { return graph; }