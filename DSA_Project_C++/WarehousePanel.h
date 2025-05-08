#pragma once

#include <wx/wx.h>
#include "supplyLocations.h"

class WarehousePanel : public wxPanel {
public:
    WarehousePanel(wxPanel* parent, supplyLocations** warehouses, int warehouseCount);

private:
    void CreateWarehouseBox(wxBoxSizer* sizer, const wxString& warehouseName, Supplies* supplies);
};
