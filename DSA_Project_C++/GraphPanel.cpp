#include "GraphPanel.h"
#include <vector>

wxBEGIN_EVENT_TABLE(GraphPanel, wxPanel)
EVT_PAINT(GraphPanel::OnPaint)
wxEND_EVENT_TABLE()

GraphPanel::GraphPanel(wxPanel* parent, Graph* graph)
    : wxPanel(parent, wxID_ANY, wxDefaultPosition, wxSize(800, 600)), graph(graph) {  // Adjusted size
}

void GraphPanel::OnPaint(wxPaintEvent& event) {
    wxPaintDC dc(this);

    // Set line color to brown
    wxPen brownPen(wxColour(139, 69, 19), 2); // RGB for brown
    dc.SetPen(brownPen);

    // Set fill color for nodes
    wxBrush nodeBrush(wxColour(135, 206, 250)); // Light blue
    dc.SetBrush(nodeBrush);

    int width = GetSize().GetWidth();
    int height = GetSize().GetHeight();

    // Define custom positions for nodes to avoid overlaps and fit within the panel
    std::vector<std::pair<int, int>> positions = {
        {width / 2, 50},       // Gaza City
        {width / 4, 150},      // Khan Younis
        {3 * width / 4, 150},  // Rafah
        {width / 6, 250},      // Jabaliya
        {5 * width / 6, 250},  // Deir-al-Balah
        {width / 4, 350},      // Nuseirat
        {3 * width / 4, 350},  // Bureij
        {width / 6, 450},      // Beach Camp
        {5 * width / 6, 450},  // Shuja'iya
        {width / 2, 550}       // Al-Maghazi
    };

    int nodeCount = positions.size();
    int nodeRadius = 30;

    // Draw nodes and labels
    for (int i = 0; i < nodeCount; i++) {
        int x = positions[i].first;
        int y = positions[i].second;
        dc.DrawCircle(wxPoint(x, y), nodeRadius);

        wxString label = graph->getLocationName(i);

        // Adjust label position for specified nodes
        if (i == 7 || i == 8 || i == 9 || i == 5) {  // Beach Camp, Shuja'iya, Al-Maghazi, Nuseirat
            dc.DrawText(label, x - dc.GetTextExtent(label).GetWidth() / 2, y + nodeRadius + 5);
        }
        else {
            dc.DrawText(label, x - dc.GetTextExtent(label).GetWidth() / 2, y - nodeRadius - 20);
        }
    }

    // Draw edges and distances
    for (int i = 0; i < nodeCount; i++) {
        for (int j = 0; j < nodeCount; j++) {
            if (i != j && graph->getRoute(i, j) != 0) {
                int x1 = positions[i].first;
                int y1 = positions[i].second;
                int x2 = positions[j].first;
                int y2 = positions[j].second;
                dc.DrawLine(wxPoint(x1, y1), wxPoint(x2, y2));

                wxString distance = wxString::Format("%d", graph->getRoute(i, j));
                int midX = (x1 + x2) / 2;
                int midY = (y1 + y2) / 2;

                // Adjust distance label position specifically for Jabaliya to Shuja'iya
                if ((i == 3 && j == 8) || (i == 8 && j == 3)) {  // Jabaliya to Shuja'iya
                    midX -= 40;  // Move label left
                    midY -= 20;  // Move label up
                }

                dc.DrawText(distance, midX, midY);
            }
        }
    }
}
