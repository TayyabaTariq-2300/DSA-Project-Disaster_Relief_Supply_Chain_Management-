#pragma once

#include <wx/treectrl.h>
#include "AffectedLoc.h"

class TreeItemData : public wxTreeItemData {
public:
    TreeItemData(AffectedLoc* location) : loc(location) {}
    AffectedLoc* GetLocation() const { return loc; }

private:
    AffectedLoc* loc;
};
