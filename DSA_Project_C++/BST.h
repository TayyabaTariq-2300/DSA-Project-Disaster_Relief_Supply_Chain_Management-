#pragma once

#include "AffectedLoc.h"

class BST {
    AffectedLoc* root;
    AffectedLoc* curr;
    AffectedLoc* prev;
    int total;

public:
    BST();
    void insert(AffectedLoc* loc, int inj);
    void Inorder(AffectedLoc* tn);
    void display();
    AffectedLoc* deleteLoc();
    AffectedLoc* getRoot();  
    AffectedLoc* getCurrentAffectedLoc() const;

};
