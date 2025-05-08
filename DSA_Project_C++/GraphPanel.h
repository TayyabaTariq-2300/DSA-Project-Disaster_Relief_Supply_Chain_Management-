#pragma once

#include <wx/wx.h>
#include <wx/scrolwin.h> // Include for wxScrolledWindow
#include "Graph.h"

class GraphPanel : public wxPanel { // Inherit from wxScrolledWindow
public:
    // Constructor accepting wxScrolledWindow* as parent
    GraphPanel(wxPanel* parent, Graph* graph);

    // Event handler for painting the panel
    void OnPaint(wxPaintEvent& event);

private:
    Graph* graph; // Pointer to the graph to be rendered

    // Macro to declare the event table for handling events
    wxDECLARE_EVENT_TABLE();
};
