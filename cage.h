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
    int getCapacity();
    string getType();
    string getName();
    string getType();
    bool isEmpty();
    bool isOvercrowded();
    int numberOfAnimal();
    vector<IAnimal*> getAnimalList();
    void addAnimal(IAnimal *newAnimal);
    void freeAnimal(IAnimal *animal);
    void setOvercrowdSickness();
    void setOvercrowdDeath(Zoo* zoo);
};

#endif