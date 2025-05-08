

#include "MyFrame.h"
#include "supplyLocations.h"

enum {
    ID_AddLocation = 1,
    ID_QuitButton,
};

wxBEGIN_EVENT_TABLE(MyFrame, wxFrame)
EVT_BUTTON(ID_AddLocation, MyFrame::OnAddAffectedLocation)
EVT_BUTTON(ID_QuitButton, MyFrame::OnQuit)
wxEND_EVENT_TABLE()

MyFrame::MyFrame(const wxString& title, Graph* graph, BST* tree, supplyLocations** warehouses, int warehouseCount)
    : wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(1200, 1000)),
    graph(graph), tree(tree) {
    
    scrollWindow = new wxScrolledWindow(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxVSCROLL | wxHSCROLL);
    scrollWindow->SetScrollRate(20, 20);

    sizer = new wxBoxSizer(wxVERTICAL);

    wxPanel* mainPanel = new wxPanel(scrollWindow, wxID_ANY);

    graphPanel = new GraphPanel(mainPanel, graph);

    treePanel = new TreePanel(mainPanel, tree);

    warehousePanel = new WarehousePanel(mainPanel, warehouses, warehouseCount);                                                                        

    nearestWarehousePanel = new NearestWarehousePanel(mainPanel, tree, warehouses, warehouseCount);

    //labels
    wxStaticText* nameLabel = new wxStaticText(mainPanel, wxID_ANY, "Location Name:");
    m_nameTextCtrl = new wxTextCtrl(mainPanel, wxID_ANY, "");

    wxStaticText* percLabel = new wxStaticText(mainPanel, wxID_ANY, "Affected Population (%)");
    m_percentageTextCtrl = new wxTextCtrl(mainPanel, wxID_ANY, "");

    wxStaticText* deadLabel = new wxStaticText(mainPanel, wxID_ANY, "Dead People:");
    m_deadTextCtrl = new wxTextCtrl(mainPanel, wxID_ANY, "");

    wxStaticText* injuredLabel = new wxStaticText(mainPanel, wxID_ANY, "Injured People:");
    m_injuredTextCtrl = new wxTextCtrl(mainPanel, wxID_ANY, "");

    m_addButton = new wxButton(mainPanel, ID_AddLocation, "Add Affected Location");
    m_quitButton = new wxButton(mainPanel, ID_QuitButton, "Quit");
    
    // Layout setup
    mainSizer = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer* inputTreeSizer = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer* inputSizer = new wxBoxSizer(wxVERTICAL);

    inputSizer->Add(nameLabel, 0, wxALL, 5);
    inputSizer->Add(m_nameTextCtrl, 0, wxALL | wxEXPAND, 5);
    inputSizer->Add(percLabel, 0, wxALL, 5);
    inputSizer->Add(m_percentageTextCtrl, 0, wxALL | wxEXPAND, 5);
    inputSizer->Add(deadLabel, 0, wxALL, 5);
    inputSizer->Add(m_deadTextCtrl, 0, wxALL | wxEXPAND, 5);
    inputSizer->Add(injuredLabel, 0, wxALL, 5);
    inputSizer->Add(m_injuredTextCtrl, 0, wxALL | wxEXPAND, 5);
    inputSizer->Add(m_addButton, 0, wxALL | wxALIGN_CENTER, 5);
    inputSizer->Add(m_quitButton, 0, wxALL | wxALIGN_CENTER, 5);

    inputTreeSizer->Add(inputSizer, 1, wxEXPAND | wxALL, 10);
    inputTreeSizer->Add(treePanel, 1, wxEXPAND | wxALL, 10);

    graphPanel->SetSize(1200, 800); 

    wxStaticText* mainHeading = new wxStaticText(mainPanel, wxID_ANY, "Disaster Relief Supply Chain Management", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT);
    mainHeading->SetFont(wxFont(18, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
    wxStaticText* subHeading = new wxStaticText(mainPanel, wxID_ANY, "Palestine", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT);
    subHeading->SetFont(wxFont(14, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));

    wxStaticText* affectedLocHeading = new wxStaticText(mainPanel, wxID_ANY, "Enter affected Locations:", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT);
    mainHeading->SetFont(wxFont(18, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));


    mainSizer->Add(mainHeading, 0, wxALIGN_CENTER | wxALL, 10);
    mainSizer->Add(subHeading, 0, wxALIGN_CENTER | wxALL, 5);
    mainSizer->Add(graphPanel, 0, wxEXPAND | wxALL, 10);  
    mainSizer->Add(affectedLocHeading, 0, wxEXPAND | wxALL, 10);
    mainSizer->Add(inputTreeSizer, 1, wxEXPAND | wxALL, 10);
    mainSizer->Add(warehousePanel, 0, wxEXPAND | wxALL, 10);
    mainSizer->Add(nearestWarehousePanel, 1, wxEXPAND | wxALL, 10);
    mainPanel->SetSizerAndFit(mainSizer);


    sizer->Add(mainPanel, 1, wxEXPAND | wxALL, 10);
    scrollWindow->SetSizer(sizer);

    sizer->Fit(scrollWindow);

    this->SetMinSize(wxSize(1200, 600));
}

void MyFrame::OnAddAffectedLocation(wxCommandEvent& event) {
    std::string name = std::string(m_nameTextCtrl->GetValue().mb_str());
    int affPer = std::stoi(std::string(m_percentageTextCtrl->GetValue().mb_str()));
    int dead = std::stoi(std::string(m_deadTextCtrl->GetValue().mb_str()));
    int injured = std::stoi(std::string(m_injuredTextCtrl->GetValue().mb_str()));

    if (!graph->isValidName(name)) {
        wxMessageBox("Location doesn't exist or is invalid. Please enter a valid location.", "Error", wxOK | wxICON_ERROR);
        return;
    }

    Locations* loc = graph->getLocationByName(name);
    if (loc != nullptr) {
        AffectedLoc* newLocation = new AffectedLoc(loc, name, affPer, dead, injured);
        tree->insert(newLocation, injured);
        affectedLocationCount++;

        wxMessageBox("Affected location added successfully.", "Success", wxOK | wxICON_INFORMATION);

        // Update the tree panel
        treePanel->UpdateTreeView();
    }

    // Reset fields after adding a location
    m_nameTextCtrl->Clear();
    m_percentageTextCtrl->Clear();
    m_deadTextCtrl->Clear();
    m_injuredTextCtrl->Clear();

    tree->display();  // Display updated tree
    graph->displayAllWarehouses();
}

void MyFrame::OnQuit(wxCommandEvent& event) {
    Close(true);  // Close the window
}


