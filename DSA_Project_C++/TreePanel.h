#pragma once

#include <wx/wx.h>
#include "BST.h"

class TreePanel : public wxPanel {
public:
    TreePanel(wxPanel* parent, BST* tree);
    void UpdateTreeView();

private:
    BST* tree;

    void OnPaint(wxPaintEvent& event);
    void OnLeftDown(wxMouseEvent& event);
    void DrawNode(wxPaintDC& dc, AffectedLoc* node, int x, int y, int horizontalOffset, int verticalOffset);
    AffectedLoc* FindNodeAtPosition(AffectedLoc* node, int searchX, int searchY, int x, int y, int horizontalOffset, int verticalOffset);

    void ShowDetailsDialog(AffectedLoc* loc);  // Ensure this declaration is present

    wxDECLARE_EVENT_TABLE();
};
