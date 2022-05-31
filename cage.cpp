#include <iostream>
#include <vector>
#include <string>
#include "config.h"
#include "cage.h"
#include "ianimal.h"

using namespace std;

Cage::Cage(string type)
{
    _type = type;
    if (type == "Tiger")
    {
        _capacity = TIGER_CAGE_CAPACITY;
    }
    else if (type == "Eagle")
    {
        _capacity = EAGLE_CAGE_CAPACITY;
    }
    else if (type == "Chicken")
    {
        _capacity = CHICKEN_CAGE_CAPACITY;
    }
    // else
    // {
    //     cout << "Unvalid type input." << endl;
    //     ~Cage();
    //     break;
    // }
    cout << "New cage created !" << endl;
}

Cage::~Cage()
{
    cout << "This cage has been removed from your zoo" << endl;
}

// return true or false if overcrowded
bool Cage::isOvercrowded()
{
    if (_capacity < numberOfAnimal())
    {
        return true;
    }
    else
    {
        return false;
    }
}

// add an animal to the cage
void Cage::addAnimal(IAnimal *newAnimal)
{
    _animal_list.push_back(newAnimal);
    cout << newAnimal->getName() << " has been added to " << getName() << endl;
}

// return the number of animals in the cage
int Cage::numberOfAnimal()
{
    return _animal_list.size();
}

// return max number of animals before surpopulation
int Cage::getCapacity()
{
    return _capacity;
}

string Cage::getName()
{
    return _type + " cage";
}

vector<IAnimal*> Cage::getAnimalList()
{
    return _animal_list;
}