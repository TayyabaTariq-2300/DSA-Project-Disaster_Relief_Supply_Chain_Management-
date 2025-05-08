#include "WarehousePanel.h"
#include <wx/listCtrl.h>
WarehousePanel::WarehousePanel(wxPanel* parent, supplyLocations** warehouses, int warehouseCount)
    : wxPanel(parent, wxID_ANY) {

    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);

    // Add heading
    wxStaticText* heading = new wxStaticText(this, wxID_ANY, "SUPPLY LOCATIONS", wxDefaultPosition, wxDefaultSize, wxALIGN_CENTER);
    heading->SetFont(wxFont(14, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
    heading->SetForegroundColour(*wxBLACK);
    mainSizer->Add(heading, 0, wxALIGN_CENTER | wxALL, 10);

    wxBoxSizer* gridSizer = new wxBoxSizer(wxHORIZONTAL);

    // Create boxes for each warehouse
    for (int i = 0; i < warehouseCount; i++) {
        CreateWarehouseBox(gridSizer, warehouses[i]->getLocation()->getName(), warehouses[i]->getSupplies());
    }

    mainSizer->Add(gridSizer, 1, wxALIGN_CENTER);

    SetSizerAndFit(mainSizer);
}

void WarehousePanel::CreateWarehouseBox(wxBoxSizer* sizer, const wxString& warehouseName, Supplies* supplies) {
    wxPanel* panel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(300, 300));
    wxBoxSizer* boxSizer = new wxBoxSizer(wxVERTICAL);

    wxStaticText* title = new wxStaticText(panel, wxID_ANY, warehouseName, wxDefaultPosition, wxDefaultSize, wxALIGN_CENTER);
    title->SetFont(wxFont(12, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
    title->SetForegroundColour(*wxBLACK);

    wxListCtrl* listCtrl = new wxListCtrl(panel, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLC_REPORT | wxLC_HRULES | wxLC_VRULES);
    listCtrl->SetBackgroundColour(*wxLIGHT_GREY);
    listCtrl->SetTextColour(*wxBLACK);
    listCtrl->SetFont(wxFont(10, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));

    // Add columns
    listCtrl->InsertColumn(0, "Supply Item");
    listCtrl->InsertColumn(1, "Quantity");

    // Add data to the list control
    long index = listCtrl->InsertItem(listCtrl->GetItemCount(), "Food");
    listCtrl->SetItem(index, 1, wxString::Format("%d", supplies->getFood()));

    index = listCtrl->InsertItem(listCtrl->GetItemCount(), "Water");
    listCtrl->SetItem(index, 1, wxString::Format("%d", supplies->getWater()));

    index = listCtrl->InsertItem(listCtrl->GetItemCount(), "Clothes");
    listCtrl->SetItem(index, 1, wxString::Format("%d", supplies->getClothes()));

    index = listCtrl->InsertItem(listCtrl->GetItemCount(), "Medicines");
    listCtrl->SetItem(index, 1, wxString::Format("%d", supplies->getMed()));

    // Adjust the width to fit the content
    listCtrl->SetColumnWidth(0, wxLIST_AUTOSIZE);
    listCtrl->SetColumnWidth(1, wxLIST_AUTOSIZE);

    boxSizer->Add(title, 0, wxEXPAND | wxALL, 5);
    boxSizer->Add(listCtrl, 1, wxEXPAND | wxALL, 5);
    panel->SetSizerAndFit(boxSizer);

    sizer->Add(panel, 1, wxEXPAND | wxALL, 10);
}
