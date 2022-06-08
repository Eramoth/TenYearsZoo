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
    // give private information
    int population();
    vector<IAnimal*> getEveryAnimalList();
    vector<Cage*> getCageList();
    vector<Cage*> getCageList(string type, string status);
    vector<IAnimal*> getAnimalListByType(string type);
    vector<IAnimal*> getAnimalListByAge(int min_age, int max_age);
    vector<IAnimal*> getAnimalListByGender(string gender);
    // show private information
    void showCageList();
    void showFoodStock();
    // modify private var functions
    void addCage(Cage* newCage);
    void addAnimal(IAnimal* newAnimal);
    void killAnimal(IAnimal* animal);
    void increaseAnimalAge();
    void withdrawAnimal(IAnimal* w_animal);
    void newSeedStock(int change);
    void newMeatStock(int change);
    void deleteCage(Cage* cage);
    void deleteCage(Cage* cage, int cage_idx);
    // event-related functions
    void monthlyUpdate();
    void feedAnimals();
    void checkForEvent();
    void checkForDisease();
    void checkDeathByDisease();
    void checkDeathByAge();
    void checkForHealing();
    void pests();
    void avariateMeat();
    void onFire();
    void stolenAnimal();
    void overcrowdSickness();
};


#endif