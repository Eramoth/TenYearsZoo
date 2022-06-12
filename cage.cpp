#include <iostream>
#include <vector>
#include <random>
#include <string>
#include "config.h"
#include "cage.h"
#include "ianimal.h"
#include "functions.h"

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
}

Cage::~Cage() {}

// return true or false if empty
bool Cage::isEmpty()
{
    if (_animal_list.size() == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
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


// return index of first chicken ; -1 if no chicken
int Cage::hasChicken()
{
    for (int i = 0 ; i < _animal_list.size(); i++)
    {
        if (_animal_list[i]->getType() == "Chicken" && !_animal_list[i]->isDead())
        {
            return i;
        }
    }
    // no one found :
    return -1;
}

// return index of first eagle ; -1 if no eagle
int Cage::hasEagle()
{
    for (int i = 0 ; i < _animal_list.size(); i++)
    {
        if (_animal_list[i]->getType() == "Eagle" && !_animal_list[i]->isDead())
        {
            return i;
        }
    }
    // no one found :
    return -1;
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

string Cage::getType()
{
    return _type;
}
string Cage::getName()
{
    return _type + " cage";
}

vector<IAnimal*> Cage::getAnimalList()
{
    return _animal_list;
}

void Cage::freeAnimal(IAnimal *animal)
{
    for (int i = 0; i < _animal_list.size(); i++)
    {
        if (_animal_list[i] == animal)
        {
            _animal_list.erase(_animal_list.begin() + i);
            return;
        }
    }
}

// set overcrowd sickness depending on type and probability
string Cage::setOvercrowdSickness()
{
    for (auto animal : _animal_list)
    {
        if (_type == "Tiger")
        {
            if (!randInt(0, 100 / TIGER_OVERCROWD_SICKNESS-1))
            {
                animal->setSick();
                cout << animal->getName() << " got sick." << endl;
            }
        }
        else if (_type == "Eagle")
        {
            if (!randInt(0, 100 / EAGLE_OVERCROWD_SICKNESS-1))
            {
                animal->setSick();
                cout << animal->getName() << " got sick." << endl;
            }
        }
        else if (_type == "Chicken")
        {
            if (!randInt(0, 100 / CHICKEN_OVERCROWD_SICKNESS-1))
            {
                animal->setSick();
                cout << animal->getName() << " got sick." << endl;
            }
        }
        else
        {
            cout << "Invalid cage type." << endl;
            return "";
        }
    }
    return ">> One of your cage is ovecrowded. Some animals got sick from it.";
}

string Cage::setOvercrowdDeath(Zoo *zoo)
{
    if (_type == "Tiger")
    {
        for (int i = 0; i<TIGER_SURPOP_LOSS; i++)
        {
            _animal_list[randInt(0, _animal_list.size()-1)]->kill(zoo);
        }
    }
    else if (_type == "Eagle")
    {
        for (int i = 0; i<TIGER_SURPOP_LOSS; i++)
        {
            _animal_list[randInt(0, _animal_list.size()-1)]->kill(zoo);
        }
    }
    else if (_type == "Chicken")
    {
        for (int i = 0; i<TIGER_SURPOP_LOSS; i++)
        {
            _animal_list[randInt(0, _animal_list.size()-1)]->kill(zoo);
        }
    }
    else
    {
        cout << "Invalid cage type." << endl;
        return "";
    }
    return ">> One of your cage is ovecroded. Some animals have died from it.";
}