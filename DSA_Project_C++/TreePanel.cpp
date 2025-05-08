#include "TreePanel.h"

wxBEGIN_EVENT_TABLE(TreePanel, wxPanel)
EVT_PAINT(TreePanel::OnPaint)
EVT_LEFT_DOWN(TreePanel::OnLeftDown)
wxEND_EVENT_TABLE()

TreePanel::TreePanel(wxPanel* parent, BST* tree)
    : wxPanel(parent), tree(tree) {
}

void TreePanel::UpdateTreeView() {
    Refresh(); // Trigger a repaint
}

void TreePanel::OnPaint(wxPaintEvent& event) {
    wxPaintDC dc(this);

    if (tree->getRoot() != nullptr) {
        // Draw the root node in the center of the panel
        int panelWidth = GetSize().GetWidth();
        int panelHeight = GetSize().GetHeight();
        int rootX = panelWidth / 2;
        int rootY = 40; // Start the root node near the top of the panel

        DrawNode(dc, tree->getRoot(), rootX, rootY, panelWidth / 6, 80);
    }
   
}

void TreePanel::DrawNode(wxPaintDC& dc, AffectedLoc* node, int x, int y, int horizontalOffset, int verticalOffset) {
    if (node == nullptr) {
        return;
    }

    // Draw the current node
    wxBrush nodeBrush(wxColour(135, 206, 250)); // Light blue
    dc.SetBrush(nodeBrush);
    dc.SetPen(*wxBLACK_PEN);
    dc.DrawCircle(wxPoint(x, y), 20);
    wxString label = wxString::Format("%s (%d)", node->getName(), node->getInjured());
    dc.DrawText(label, x - dc.GetTextExtent(label).GetWidth() / 2, y - 40);

    // Set pen color for lines
    wxPen linePen(wxColour(34, 139, 34), 2); 
    dc.SetPen(linePen);

    // Draw left child
    if (node->getLeft() != nullptr) {
        int childX = x - horizontalOffset;
        int childY = y + verticalOffset;
        dc.DrawLine(x, y + 20, childX, childY - 20); 
        DrawNode(dc, node->getLeft(), childX, childY, horizontalOffset / 2, verticalOffset);
    }

    // Draw right child
    if (node->getRight() != nullptr) {
        int childX = x + horizontalOffset;
        int childY = y + verticalOffset;
        dc.DrawLine(x, y + 20, childX, childY - 20);
        DrawNode(dc, node->getRight(), childX, childY, horizontalOffset / 2, verticalOffset);
    }
}

void TreePanel::OnLeftDown(wxMouseEvent& event) {
    int x = event.GetX();
    int y = event.GetY();

    AffectedLoc* node = FindNodeAtPosition(tree->getRoot(), x, y, GetSize().GetWidth() / 2, 40, GetSize().GetWidth() / 6, 80);
    if (node) {
        ShowDetailsDialog(node);
    }
}

AffectedLoc* TreePanel::FindNodeAtPosition(AffectedLoc* node, int searchX, int searchY, int x, int y, int horizontalOffset, int verticalOffset) {
    if (node == nullptr) {
        return nullptr;
    }

    int radius = 20;
    if (abs(searchX - x) <= radius && abs(searchY - y) <= radius) {
        return node;
    }

    AffectedLoc* foundNode = nullptr;

    // Search left child
    if (node->getLeft() != nullptr) {
        int childX = x - horizontalOffset;
        int childY = y + verticalOffset;
        foundNode = FindNodeAtPosition(node->getLeft(), searchX, searchY, childX, childY, horizontalOffset / 2, verticalOffset);
    }

    // Search right child
    if (foundNode == nullptr && node->getRight() != nullptr) {
        int childX = x + horizontalOffset;
        int childY = y + verticalOffset;
        foundNode = FindNodeAtPosition(node->getRight(), searchX, searchY, childX, childY, horizontalOffset / 2, verticalOffset);
    }

    return foundNode;
}

void TreePanel::ShowDetailsDialog(AffectedLoc* loc) {
    wxString message = wxString::Format("Location: %s\nTotal Population: %d\nAffected: %s\nAffected Percentage: %d\nDead People: %d\nInjured People: %d",
        loc->getName(), loc->getTotalPop(), "Yes",
        loc->getAffectedPopPer(), loc->getDead(), loc->getInjured());
    wxMessageBox(message, "Location Details", wxOK | wxICON_INFORMATION, this);
}
