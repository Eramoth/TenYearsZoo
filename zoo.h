#ifndef ZOO_H
#define ZOO_H

#include <vector>
#include "ianimal.h"
#include "cage.h"

using namespace std;

class IAnimal;
class Cage;

class Zoo {
private:
    vector<Cage*> _cage_list;
    int _meat_stock;
    int _seed_stock;
    // int money; // a décommenter + modif le code avec money
public:
    Zoo();
    ~Zoo();
    void addCage(Cage* newCage);
    void addAnimal(IAnimal* newAnimal);
    void withdrawAnimal(IAnimal* w_animal);
    void feedAnimals();
    void checkForEvent();
    void checkForDisease();
    int population();
    vector<Cage*> getCageList();
    void monthlyUpdate();
    void showCageList();
    void buyFood(int *money);
    void showFoodStock();
    void newSeedStock(int change);
    void newMeatStock(int change);
};


#endif