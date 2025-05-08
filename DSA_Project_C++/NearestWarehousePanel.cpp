#define _CRT_SECURE_NO_WARNINGS
#include "NearestWarehousePanel.h"
#include <wx/dcbuffer.h>
#include <wx/listctrl.h>
#include <vector>

enum {
    ID_FindNearestWarehouses = wxID_HIGHEST + 1  // Unique ID for the Find Nearest Warehouses button
};

wxBEGIN_EVENT_TABLE(NearestWarehousePanel, wxPanel)
    EVT_PAINT(NearestWarehousePanel::OnPaint)
    EVT_BUTTON(ID_FindNearestWarehouses, NearestWarehousePanel::FindNearestWarehouses)  // Added
wxEND_EVENT_TABLE()

NearestWarehousePanel::NearestWarehousePanel(wxPanel* parent, BST* bst, supplyLocations** warehouses, int warehouseCount)
    : wxPanel(parent, wxID_ANY), bst(bst), warehouses(warehouses), warehouseCount(warehouseCount) {

    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);

    // Add heading
    wxStaticText* heading = new wxStaticText(this, wxID_ANY, "NEAREST WAREHOUSE TO AFFECTED LOCATION", wxDefaultPosition, wxDefaultSize, wxALIGN_CENTER);
    heading->SetFont(wxFont(14, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
    heading->SetForegroundColour(*wxBLACK);
    mainSizer->Add(heading, 0, wxALIGN_CENTER | wxALL, 10);

    // Add button to find nearest warehouses
    wxButton* findNearestButton = new wxButton(this, ID_FindNearestWarehouses, "Find Nearest Warehouses");
    mainSizer->Add(findNearestButton, 0, wxALIGN_CENTER | wxALL, 10);

    SetSizerAndFit(mainSizer);
}

void NearestWarehousePanel::FindNearestWarehouses(wxCommandEvent& event) {  // Added wxCommandEvent& parameter

    affectedLocs.clear();
    nearestWarehouses.clear();
    distances.clear();

    // Helper function to traverse the BST and collect all affected locations
    std::function<void(AffectedLoc*)> collectLocations = [&](AffectedLoc* node) {
        if (node != nullptr) {
            collectLocations(node->getLeft());
            affectedLocs.push_back(node);
            collectLocations(node->getRight());
        }
    };

    // Traverse the BST from the root
    collectLocations(bst->getRoot());

    if (affectedLocs.empty()) {
        // No affected locations to process
        wxMessageBox("No affected locations to process.", "Information", wxOK | wxICON_INFORMATION);
        return;
    }

    for (auto loc : affectedLocs) {

        warehouses[0]->calculateItems(loc);

        // Find the nearest warehouse
        int nearestWarehouseIndex = -1;
        int minDistance = INT_MAX;
        int dist[10];
        int prev[10];
        int affectedIndex = -1;

        // Find the index of the affected location in the locations array
        Locations* locations = warehouses[0]->getGraph()->getLocations();
        for (int i = 0; i < 10; i++) {
            if (locations[i].getName() == loc->getName()) {
                affectedIndex = i;
                break;
            }
        }

        if (affectedIndex == -1) {
            wxMessageBox("Affected location not found in the graph.", "Error", wxOK | wxICON_ERROR);
            continue;
        }

        // Run Dijkstra's algorithm from the affected location
        warehouses[0]->getGraph()->dijkstra(affectedIndex, dist, prev);

        // Find the nearest warehouse
        supplyLocations** locs = warehouses[0]->getGraph()->getSupplyLocations();
        for (int i = 0; i < 3; i++) {
            int warehouseIndex = -1;
            for (int j = 0; j < 10; j++) {
                if (locations[j].getName() == locs[i]->getLocation()->getName()) {
                    warehouseIndex = j;
                    break;
                }
            }
            if (warehouseIndex != -1 && dist[warehouseIndex] < minDistance) {
                minDistance = dist[warehouseIndex];
                nearestWarehouseIndex = warehouseIndex;
            }
        }

        if (nearestWarehouseIndex != -1) {
            nearestWarehouses.push_back(&locations[nearestWarehouseIndex]);
            distances.push_back(minDistance);
            // Call deliverSupplies to update the supplies
            warehouses[0]->deliverSupplies(loc);
        }
    }

    // Refresh to trigger OnPaint
    Refresh();
}

void NearestWarehousePanel::OnPaint(wxPaintEvent& event) {
    wxBufferedPaintDC dc(this);
    dc.Clear();

    if (affectedLocs.empty() || nearestWarehouses.empty()) {
        return;
    }

    for (size_t i = 0; i < affectedLocs.size(); ++i) {
        // Calculate the horizontal offset for each pair
        int offsetX = i * 300;

        // Draw affected location
        dc.SetBrush(*wxBLUE_BRUSH);
        dc.DrawCircle(wxPoint(100 + offsetX, 100), 20);
        // Display affected location name
        dc.DrawText(affectedLocs[i]->getName(), wxPoint(80 + offsetX, 130));

        // Display affected location supplies
        Supplies affectedSupplies = affectedLocs[i]->getSupplies();
        dc.DrawText("Food: " + std::to_string(affectedSupplies.getFood()), wxPoint(80 + offsetX, 150));
        dc.DrawText("Water: " + std::to_string(affectedSupplies.getWater()), wxPoint(80 + offsetX, 170));
        dc.DrawText("Clothes: " + std::to_string(affectedSupplies.getClothes()), wxPoint(80 + offsetX, 190));
        dc.DrawText("Med: " + std::to_string(affectedSupplies.getMed()), wxPoint(80 + offsetX, 210));

        // Draw nearest warehouse
        dc.SetBrush(*wxRED_BRUSH);
        dc.DrawCircle(wxPoint(300 + offsetX, 100), 20);
        // Display warehouse name
        dc.DrawText(nearestWarehouses[i]->getName(), wxPoint(280 + offsetX, 130));

        // Display nearest warehouse supplies
        Supplies warehouseSupplies = nearestWarehouses[i]->getOriginalSupplies();
        dc.DrawText("Food: " + std::to_string(warehouseSupplies.getFood()), wxPoint(280 + offsetX, 150));
        dc.DrawText("Water: " + std::to_string(warehouseSupplies.getWater()), wxPoint(280 + offsetX, 170));
        dc.DrawText("Clothes: " + std::to_string(warehouseSupplies.getClothes()), wxPoint(280 + offsetX, 190));
        dc.DrawText("Med: " + std::to_string(warehouseSupplies.getMed()), wxPoint(280 + offsetX, 210));

        // Draw line connecting affected location and nearest warehouse
        dc.DrawLine(wxPoint(100 + offsetX, 100), wxPoint(300 + offsetX, 100));

        // Display distance on the line
        int midX = (100 + offsetX + 300 + offsetX) / 2;
        int midY = 90;
        dc.DrawText( std::to_string(distances[i]), wxPoint(midX, midY - 10));
    }
}

