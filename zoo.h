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
    void checkDeathByAge();
    void increaseAnimalAge();
    int population();
    vector<Cage*> getCageList();
    void monthlyUpdate();
    void showCageList();
    void buyFood(int *money);
    void showFoodStock();
    void newSeedStock(int change);
    void newMeatStock(int change);
    void pests();
    void avariateMeat();
    void killAnimal(IAnimal* animal);
    void deleteCage(Cage* cage);
    void deleteCage(Cage* cage, int cage_idx);
    vector<IAnimal*> getAnimalListByAge(string type_name, int min_age, int max_age);
    vector<IAnimal*> getAnimalListByGender(string type_name, string gender);
    vector<Cage*> getCageList(string type, string status);
    void onFire();
    void stolenAnimal();
    void overcrowdSickness();
};


#endif