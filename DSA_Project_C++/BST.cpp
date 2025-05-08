#define _CRT_SECURE_NO_WARNINGS
#include "BST.h"
#include <iostream>
#include <wx/wx.h>

BST::BST() : root(nullptr), curr(nullptr), prev(nullptr), total(0) {}

void BST::insert(AffectedLoc* loc, int inj) {
    AffectedLoc* newNode = loc;

    std::cout << "Injured People: " << newNode->getInjured() << std::endl;

    if (root == nullptr) {
        std::cout << "\nRoot is nullptr. Setting newNode as root.\n";
        root = newNode;
        wxLogMessage("Inserted as the root");
    }
    else {
        curr = root;
        prev = nullptr;

        while (curr != nullptr) {
            prev = curr;
            if (inj < curr->getInjured()) {
                curr = curr->getLeft();
                if (curr == nullptr) {
                    prev->setLeft(newNode);
                    std::cout << "Inserted " << newNode->getInjured() << " to the left of " << prev->getInjured() << ".\n";
                }
            }
            else {
                curr = curr->getRight();
                if (curr == nullptr) {
                    prev->setRight(newNode);
                    std::cout << "Inserted " << newNode->getInjured() << " to the right of " << prev->getInjured() << ".\n";
                }
            }
        }
    }

    total++;
    std::cout << "\nRoot is now: " << root << " with injured: " << root->getInjured() << std::endl;
}

void BST::Inorder(AffectedLoc* tn) {
    if (tn != nullptr) {
        Inorder(tn->getLeft());
        tn->displayAffectedDetails();
        Inorder(tn->getRight());
    }
}

void BST::display() {
    std::cout << "\nDisplaying BST:\n";
    std::cout << "Current root: " << root << std::endl;
    if (root == nullptr) {
        std::cout << "Tree is empty inside display function.\n";
    }
    else {
        std::cout << "\n============== Affected Locations ==============\n";
        std::cout << "\nInorder Traversal of the BST (Injured Count):\n";
        std::cout << "\n\t\tTotal affected locations: " << total << std::endl;
        Inorder(root);
    }
}

AffectedLoc* BST::deleteLoc() {
    if (root == nullptr) {
        std::cout << "\nRoot is nullptr. Tree is empty.\n";
        return nullptr;
    }
    curr = root;
    prev = nullptr;

    while (curr->getRight() != nullptr) {
        prev = curr;
        curr = curr->getRight();
    }

    curr->markAsServed();
    AffectedLoc* deletedLoc = curr;

    if (curr->getLeft() != nullptr) {
        if (prev == nullptr) {
            root = curr->getLeft();
        }
        else if (prev->getRight() == curr) {
            prev->setRight(curr->getLeft());
        }
        else {
            prev->setLeft(curr->getLeft());
        }
    }
    else {
        if (prev == nullptr) {
            root = nullptr;
        }
        else if (prev->getRight() == curr) {
            prev->setRight(nullptr);
        }
        else {
            prev->setLeft(nullptr);
        }
    }

    total--;
    std::cout << "\n=============Location " << deletedLoc->getName() << " with injured count " << deletedLoc->getInjured() << " is served.==============\n";
    return deletedLoc;
}

AffectedLoc* BST::getRoot() {
    return root;
}

AffectedLoc* BST::getCurrentAffectedLoc() const {
    return curr;  // Assuming curr is the current affected location
}