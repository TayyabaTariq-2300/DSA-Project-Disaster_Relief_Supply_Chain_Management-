//#pragma once
//
//#include <wx/wx.h>
//#include "BST.h"
//#include "supplyLocations.h"
//
//class NearestWarehousePanel : public wxPanel {
//public:
//    NearestWarehousePanel(wxPanel* parent, BST* bst, supplyLocations** warehouses, int warehouseCount);
//    void FindNearestWarehouse(wxCommandEvent& event);
//
//    void OnFindNearestWarehouse(wxCommandEvent& event);
//
//private:
//    void OnPaint(wxPaintEvent& event);
//
//    BST* bst;
//    supplyLocations** warehouses;
//    int warehouseCount;
//    AffectedLoc* affectedLoc;
//    Locations* nearestWarehouse;
//
//    wxDECLARE_EVENT_TABLE();
//};


#pragma once
#include <wx/wx.h>
#include "BST.h"
#include "supplyLocations.h"


#include <vector>  // Added

class NearestWarehousePanel : public wxPanel {
public:
    NearestWarehousePanel(wxPanel* parent, BST* bst, supplyLocations** warehouses, int warehouseCount);
    void FindNearestWarehouses(wxCommandEvent& event);

    std::vector<int> distances;

private:
    void OnPaint(wxPaintEvent& event);

    BST* bst;
    supplyLocations** warehouses;
    int warehouseCount;
    std::vector<AffectedLoc*> affectedLocs;  // Added
    std::vector<Locations*> nearestWarehouses;  // Added

    wxBoxSizer* horizontalSizer; // Declare horizontalSizer

    wxDECLARE_EVENT_TABLE();
};
