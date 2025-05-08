
#pragma once

#include <wx/wx.h>
#include "Graph.h"
#include "BST.h"
#include "GraphPanel.h"
#include "TreePanel.h"
#include "WarehousePanel.h"
#include "NearestWarehousePanel.h"
#include <vector>  // Add this line

class MyFrame : public wxFrame {
public:
    MyFrame(const wxString& title, Graph* graph, BST* tree, supplyLocations** warehouses, int warehouseCount);

private:
    void OnAddAffectedLocation(wxCommandEvent& event);
    void OnQuit(wxCommandEvent& event);

    wxScrolledWindow* scrollWindow;
    wxBoxSizer* sizer;
    wxPanel* mainPanel;
    GraphPanel* graphPanel;
    TreePanel* treePanel;
    WarehousePanel* warehousePanel;
    NearestWarehousePanel* nearestWarehousePanel;

    wxBoxSizer* mainSizer;
    wxTextCtrl* m_nameTextCtrl;
    wxTextCtrl* m_percentageTextCtrl;
    wxTextCtrl* m_deadTextCtrl;
    wxTextCtrl* m_injuredTextCtrl;
    wxButton* m_addButton;
    wxButton* m_quitButton;

    Graph* graph;
    BST* tree;
    int affectedLocationCount = 0;
    wxDECLARE_EVENT_TABLE();
};


