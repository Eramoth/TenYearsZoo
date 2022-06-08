#ifndef CAGE_H
#define CAGE_H

#include <string>
#include <vector>
#include "ianimal.h"

using namespace std;

class IAnimal;

class Cage
{
private:
    int _capacity;
    string _type;
    vector<IAnimal*> _animal_list;
public:
    Cage(string type);
    ~Cage();
    // give private information
    int getCapacity();
    string getType();
    string getName();
    bool isEmpty();
    bool isOvercrowded();
    int numberOfAnimal();
    vector<IAnimal*> getAnimalList();
    // modify private information
    void addAnimal(IAnimal *newAnimal);
    void freeAnimal(IAnimal *animal);
    string setOvercrowdSickness();
    string setOvercrowdDeath(Zoo* zoo);
};

#endif