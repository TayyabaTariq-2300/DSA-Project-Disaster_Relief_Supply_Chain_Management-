// Graph.cpp

#define _CRT_SECURE_NO_WARNINGS
#include "Graph.h"
#include "Locations.h"
#include "supplyLocations.h"
#include "BST.h"
#include "Supplies.h"
#include <iostream>
#include <iomanip>
#include<string>


using namespace std;
Graph::Graph(BST* sharedTree) {
	locations[0] = { "Gaza City", 400135 };
	locations[1] = { "Khan Younis", 135001 };
	locations[2] = { "Rafah", 250000 };
	locations[3] = { "Jabaliya", 90000 };
	locations[4] = { "Deir-al-Balah", 10000 };
	locations[5] = { "Nuseirat", 18902 };
	locations[6] = { "Bureij", 23909 };
	locations[7] = { "Beach Camp", 32189 };
	locations[8] = { "Shuja'iya", 189012 };
	locations[9] = { "Al-Maghazi", 45300 };

	tree = sharedTree;
	locs[0] = new supplyLocations(&locations[4], tree, this);
	locs[1] = new supplyLocations(&locations[8], tree, this);
	locs[2] = new supplyLocations(&locations[9], tree, this);


	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			routes[i][j] = 0;
		}
	}

	routes[0][1] = 20; // Gaza City to Khan Younis
	routes[0][2] = 30; // Gaza City to Rafah
	routes[0][3] = 25; // Gaza City to Jabaliya
	routes[0][4] = 40; // Gaza City to Deir-al-Balah
	routes[0][8] = 20;//shujaija
	routes[0][9] = 30;//al maghazi

	// Khan Younis
	routes[1][0] = 20; // Khan Younis to Gaza City
	routes[1][2] = 15; // Khan Younis to Rafah
	routes[1][4] = 20; // Khan Younis to Deir-al-Balah
	routes[1][5] = 10; // Khan Younis to Nuseirat
	routes[1][8] = 15;//shujaija
	routes[1][9] = 40;//al maghazi

	// Rafah
	routes[2][0] = 30; // Rafah to Gaza City
	routes[2][1] = 15; // Rafah to Khan Younis
	routes[2][3] = 35; // Rafah to Jabaliya
	routes[2][4] = 9;
	routes[2][8] = 25; // Rafah to Shuja'iya
	routes[2][9] = 20;//al maghazi

	// Jabaliya
	routes[3][0] = 25; // Jabaliya to Gaza City
	routes[3][2] = 35; // Jabaliya to Rafah
	routes[3][7] = 15; // Jabaliya to Beach Camp
	routes[3][8] = 10;//shujaija
	routes[3][9] = 32;//al maghazi

	// Deir-al-Balah
	routes[4][0] = 40; // Deir-al-Balah to Gaza City
	routes[4][1] = 20; // Deir-al-Balah to Khan Younis
	routes[4][2] = 9;
	routes[4][5] = 15; // Deir-al-Balah to Nuseirat
	routes[4][8] = 14;//shujaija
	routes[4][9] = 38;//al maghazi

	// Nuseirat
	routes[5][1] = 10; // Nuseirat to Khan Younis
	routes[5][4] = 15; // Nuseirat to Deir-al-Balah
	routes[5][6] = 5;  // Nuseirat to Bureij
	routes[5][8] = 22;//shujaija
	routes[5][9] = 10;//al maghazi

	// Bureij
	routes[6][5] = 5; // Bureij to Nuseirat
	routes[6][7] = 12; // Bureij to Beach Camp
	routes[6][8] = 27;//shujaija
	routes[6][9] = 31;//al maghazi

	// Beach Camp
	routes[7][3] = 15; // Beach Camp to Jabaliya
	routes[7][6] = 12; // Beach Camp to Bureij
	routes[7][8] = 18; // Beach Camp to Shuja'iya
	routes[7][9] = 33;//al maghazi

	// Shuja'iya
	routes[8][0] = 20;
	routes[8][1] = 15;
	routes[8][2] = 25; // Shuja'iya to Rafah
	routes[8][3] = 10; // Shuja'iya to Jabaliya
	routes[8][4] = 14;
	routes[8][5] = 22;
	routes[8][6] = 27;
	routes[8][7] = 18; // Shuja'iya to Beach Camp
	routes[8][9] = 30; // Shuja'iya to Al-Maghazi

	// Al-Maghazi
	routes[9][0] = 30;
	routes[9][1] = 40;
	routes[9][2] = 20;
	routes[9][3] = 32;
	routes[9][4] = 38;
	routes[9][5] = 10;
	routes[9][6] = 31;
	routes[9][7] = 33;
	routes[9][8] = 30; // Al-Maghazi to Shuja'iya
}

Locations* Graph::getLocations() {
	return locations;
}

supplyLocations** Graph::getSupplyLocations() {
	return locs;
}

int Graph::minDistance(int dist[], bool sptSet[]) {
	int min = INT_MAX, min_index;

	for (int v = 0; v < 10; v++) {
		if (!sptSet[v] && dist[v] <= min) {
			min = dist[v];
			min_index = v;
		}
	}

	return min_index;
}

Locations* Graph::getLocationByName(const string& name) {
	for (int i = 0; i < 10; i++) {
		if (locations[i].getName() == name) {
			return &locations[i];
		}
	}
	return nullptr;
}


void Graph::handleSupplyChain(int totalAffected) {
	for (int i = 0; i < totalAffected; i++) {
		AffectedLoc* deletedAffLoc1 = tree->deleteLoc();
		locs[i]->calculateItems(deletedAffLoc1);
		locs[i]->deliverSupplies(deletedAffLoc1);
	}
}


void Graph::displayAllWarehouses() {
	cout << "\n=======WareHouses==========\n";
	for (int i = 0; i < 3; ++i) {
		cout << "\nWarehouse " << i + 1 << ": ";
		locs[i]->displaySupplyDetails(); //inside supplyLocations class.

		cout << endl;
	}
}

bool Graph::isValidName(const string& name) {
	for (int i = 0; i < 10; i++) {
		if (name.empty()) {
			return false; // Empty name is invalid
		}
		if (locations[i].getName() == name) {
			return true; // name valid
		}
	}
	return false;
}

void Graph::displayLocations() {
	cout << "\n=======Locations============\n";
	for (int i = 0; i < 10; i++) {
		locations[i].displayLocation();
	}
}

void Graph::displayRoutes() {
	const int WIDTH = 14; // Adjust column width as needed for alignment
	cout << "\n\tDistances Between Locations (Adjacency Matrix):\n\n";

	// Print column headers (location names)
	cout << setw(WIDTH) << " ";
	for (int i = 0; i < 10; i++) {
		cout << setw(WIDTH) << locations[i].getName();
	}
	cout << endl;

	// Print matrix with distances
	for (int i = 0; i < 10; i++) {
		// Print row header (location name)
		cout << setw(WIDTH) << locations[i].getName();
		for (int j = 0; j < 10; j++) {
			cout << setw(WIDTH) << routes[i][j];
		}
		cout << endl;
	}
}

void Graph::dijkstra(int src, int dist[], int prev[]) {
	bool sptSet[10]; // sptSet[i] will be true if vertex i is included in shortest path tree

	// Initialize all distances as INFINITE and sptSet[] as false
	for (int i = 0; i < 10; i++) {
		dist[i] = INT_MAX;
		sptSet[i] = false;
		prev[i] = -1; // Initialize previous node array
	}

	// Distance of source vertex from itself is always 0
	dist[src] = 0;

	// Find shortest path for all vertices
	for (int count = 0; count < 9; count++) {
		// Pick the minimum distance vertex from the set of vertices not yet processed
		int u = minDistance(dist, sptSet);

		// Mark the picked vertex as processed
		sptSet[u] = true;

		// Update dist value of the adjacent vertices of the picked vertex
		for (int v = 0; v < 10; v++) {
			// Update dist[v] only if is not in sptSet, there is an edge from u to v, and total weight of path from src to v through u is smaller than current value of dist[v]
			if (!sptSet[v] && routes[u][v] && dist[u] != INT_MAX && dist[u] + routes[u][v] < dist[v]) {
				dist[v] = dist[u] + routes[u][v];
				prev[v] = u; // Store the previous node
			}
		}
	}

}


// New method to get location names for display
string Graph::getLocationName(int index) {
	return locations[index].getName();  // Assuming Location has a getName() method
}

// New method to get routes between locations
int Graph::getRoute(int from, int to) {
	return routes[from][to];
}

