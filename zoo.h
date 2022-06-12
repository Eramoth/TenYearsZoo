#ifndef ZOO_H
#define ZOO_H

#include <vector>
#include <string>
#include "ianimal.h"
#include "cage.h"

using namespace std;

class IAnimal;
class Cage;

class Zoo {
private:
    vector<Cage*> _cage_list;
    float _meat_stock;
    float _seed_stock;
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
    float getMeatStock();
    float getSeedStock();
    // show private information
    void showCageList(int,int,int);
    void showFoodStock();
    // modify private var functions
    void addCage(Cage* newCage);
    void addAnimal(IAnimal* newAnimal);
    void killAnimal(IAnimal* animal);
    void increaseAnimalAge(string *story);
    void withdrawAnimal(IAnimal* w_animal);
    void newSeedStock(float change);
    void newMeatStock(float change);
    void deleteCage(Cage* cage);
    void deleteCage(Cage* cage, int cage_idx);
    // event-related functions
    void monthlyUpdate(string* story, int month, int* money);
    void massReproduce(string* story,int month);
    void feedAnimals(string* story);
    void checkForTurism(string* story, int month, int* money);
    void checkForEvent(string* story);
    void checkForDisease(string* story);
    void checkForBirths(string* story);
    void checkDeathByDisease(string* story);
    void checkDeathByAge(string* story);
    void checkForHealing(string* story);
    void pests(string* story);
    void avariateMeat(string* story);
    void onFire(string* story);
    void stolenAnimal(string* story);
    void overcrowdSickness(string* story);
};


#endif