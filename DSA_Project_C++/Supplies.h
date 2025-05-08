#pragma once
#pragma once

class Supplies {
    int food, water, med, clothes;
public:
    Supplies();
    void setFoodWaterClothes(int tp, int d);
    void updateFoodWaterClothes(int f, int w, int c);
    void updateMed(int m);
    void setMed(int injured);
    int getFood() const;
    int getWater() const;
    int getClothes() const;
    int getMed() const;
    void displaySupplies();
};

