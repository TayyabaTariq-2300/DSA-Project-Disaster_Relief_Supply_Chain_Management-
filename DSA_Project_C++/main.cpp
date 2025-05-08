//#define _CRT_SECURE_NO_WARNINGS
//#include <iostream>
//#include <string>
//#include <future> // Include the future header for std::async
//#include "Graph.h"
//#include "BST.h"
//#include "Locations.h"
//#include "AffectedLoc.h"
//#include "Supplies.h"
//#include "supplyQueue.h"
//#include "supplyLocations.h"
//
//#include "wx/wx.h" // wxWidgets include
//#include "MyApp.h" // wxWidgets app logic
//#include "GraphPanel.h" // Custom panel for graph
//#include "myFrame.h"
//
//using namespace std;
//
//void runWxWidgets(Graph* graph) {
//
//    cout << "Inside run.";
//
//    wxApp::SetInstance(new MyApp());
//    wxEntryStart(0, nullptr);
//    wxTheApp->CallOnInit();
//
//    MyFrame* frame = new MyFrame(graph);
//    frame->Show(true);
//
//    wxTheApp->OnRun();
//    wxEntryCleanup();
//}
//
//int main() {
//
//    cout << "Inside main.";
//
//    BST* tree = new BST();
//
//    Graph g(tree);
//    g.displayLocations();
//    g.displayRoutes();
//
//    // Run wxWidgets event loop asynchronously
//    //auto wxFuture = std::async(std::launch::async, runWxWidgets, &g);
//    int ch;
//    cout << "\n\tHow many affected locations do you want to add? ";
//    cin >> ch;
//    while (ch > 7) {
//        cout << "\nAffected locations cannot be more than total locations (10).";
//        cout << " Enter again: ";
//        cin >> ch;
//    }
//
//    string n;
//    int d, injured;
//    float affPer;
//    for (int i = 0; i < ch; i++) {
//        cout << "\n\tEnter affected location:";
//        cout << "\nName: ";
//        cin.ignore();
//        getline(cin, n);
//        while (!g.isValidName(n)) {
//            if (n.empty()) {
//                cout << "\nLocation name cannot be empty. Please enter a valid location.";
//            }
//            else {
//                cout << "\nLocation doesn't exist. Enter again.";
//            }
//            cout << "\nEnter name: ";
//            getline(cin, n);
//        }
//
//        cout << "Affected Population Percentage: ";
//        cin >> affPer;
//        cout << "Dead People: ";
//        cin >> d;
//        cout << "Injured People: ";
//        cin >> injured;
//
//        Locations* loc = g.getLocationByName(n);
//        if (loc != nullptr) {
//            AffectedLoc* newLocation = new AffectedLoc(loc, n, affPer, d, injured);
//            tree->insert(newLocation, injured);
//        }
//    }
//
//    tree->display();
//    g.displayAllWarehouses();
//
//    g.handleSupplyChain(ch);
//
//
//    // Wait for wxWidgets event loop to finish
//    //wxFuture.get();
//
//    return 0;
//}
