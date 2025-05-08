#define _CRT_SECURE_NO_WARNINGS
#include "MyApp.h"
#include "MyFrame.h"
#include "supplyLocations.h"

bool MyApp::OnInit() {
    BST* tree = new BST(); // Initialize tree
    Graph* graph = new Graph(tree); // Create graph object

    // Assuming you have created supplyLocations for the warehouses
    supplyLocations** warehouses = new supplyLocations * [3];
    warehouses[0] = new supplyLocations(&graph->getLocations()[4], tree, graph); // Deir-al-Balah
    warehouses[1] = new supplyLocations(&graph->getLocations()[8], tree, graph); // Shuja'iya
    warehouses[2] = new supplyLocations(&graph->getLocations()[9], tree, graph); // Al-Maghazi

    int warehouseCount = 3; // Number of warehouses

    // Create MyFrame with the required arguments
    MyFrame* frame = new MyFrame("Graph Visualization", graph, tree, warehouses, warehouseCount);
    frame->Show(true);
    return true;
}

wxIMPLEMENT_APP(MyApp);
