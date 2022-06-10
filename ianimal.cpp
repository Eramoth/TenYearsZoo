#include <iostream>
#include <string>
#include <vector>
#include "zoo.h"
#include "ianimal.h"
#include "config.h"
#include "cage.h"

using namespace std;

// ask for a name, then create an object animal with name, age, gender
IAnimal::IAnimal(string type, int age, int gender, int age_of_death)
{
    cout << ">> New animal name : ";
    cin >> _name;
    cout << _name << " is waiting in the zoo."
         << endl
         << endl;
    _type = type;
    _age = age;
    _age_of_death = age_of_death;
    _gender = gender;
    _is_hungry = false;
    _gestation_month;
    _is_sick = false;
    _fresh_new = true;
}

IAnimal::~IAnimal()
{
    cout << _name << " has been deleted." << endl;
}

// will delete the animal from the zoo, then erase it from memory
void IAnimal::kill(Zoo *zoo)
{
    zoo->withdrawAnimal(this);
    delete this;
}

// return name of animal
string IAnimal::getName()
{
    return _name;
}

// return Tiger, Chicken or Eagle depending on animal's type
string IAnimal::getType()
{
    if (_type == "")
    {
        cout << "No type found." << endl;
        return "";
    }
    return _type;
}

// return the age (month) of the animal
int IAnimal::getAge()
{
    return _age;
}

int IAnimal::getGestationMonth()
{
    return _gestation_month;
}

// return true if sick, false if healthy
bool IAnimal::isSick()
{
    return _is_sick;
}

bool IAnimal::isPregnant()
{
    return _gestation_month >= 0;
}

//return gender of animal
string IAnimal::getGender()
{
    if (_gender == 1)
    {
        return "male";
    }
    else
    {
        return "female";
    }
}

// check if animal has been fed last month
bool IAnimal::isHungry()
{
    return _is_hungry;
}

// add one month to animal age ; if too old, kill it
void IAnimal::increaseAge(Zoo *zoo)
{
    _age++;
    _fresh_new = false;
    if (isPregnant())
    {
        _gestation_month++;
    }
    if (_age >= _age_of_death)
    {
        cout << "<< " <<  _name << " died after a long life." << endl;
        kill(zoo);
    }
}

// escape from the zoo (animal is then killed)
void IAnimal::escape(Zoo *zoo)
{
    cout << getName() << " escaped from the zoo." << endl;
    kill(zoo);
}

// update sick statut
void IAnimal::setSick()
{
    _is_sick = true;
}

void IAnimal::setPregnancy(bool is_pregnant)
{
    if (is_pregnant)
    {
        _gestation_month = 0;
    }
    else
    {
        _gestation_month = -1;
    }
}


void IAnimal::setCured()
{
    _is_sick = false;
    cout << getName() << "'s sickness got cured, and he even kept one of it's leg healthy !" << endl;
}

void IAnimal::setPartner(IAnimal* partner)
{
    _partner = partner;
}

IAnimal* IAnimal::getPartner()
{
    return _partner;
}

// ----- TIGER -----
Tiger::Tiger(int age, int gender) : IAnimal("Tiger", age, gender, TIGER_LIFESPAWN) {}

// will print the type, age and gender of the animal
void Tiger::showAnimal()
{
    cout << "Tiger, " << getGender() << ", " << getAge() << " month(s), " << endl;
}

// return true if animal is up for reproduction, false if not
bool Tiger::canReproduce()
{
    // if male
    if (_gender == 1)
    {
        if (_age >= MALE_TIGER_MATURITY * 12 && _age < MALE_TIGER_UNFERTILITY_AGE * 12 && !_is_sick && !_fresh_new)
        {
            return true;
        }
    }
    // if female
    else if (_gender == 2)
    {
        if (_age >= FEMALE_TIGER_MATURITY * 12 && _age < FEMALE_TIGER_UNFERTILITY_AGE * 12 && !isPregnant() && !_is_sick && !_fresh_new)
        {
            return true;
        }
    }
    return false;
}

// ----- EAGLE -----
Eagle::Eagle(int age, int gender) : IAnimal("Eagle", age, gender, EAGLE_LIFESPAWN) {}

// will print the type, age and gender of the animal
void Eagle::showAnimal()
{
    cout << "Eagle, " << getGender() << ", " << getAge() << " month(s), " << endl;
}

// return true if animal is up for reproduction, false if not
bool Eagle::canReproduce()
{
    // if male
    if (_gender == 1)
    {
        if (_age >= MALE_EAGLE_MATURITY && _age < MALE_EAGLE_UNFERTILITY_AGE && !_is_sick && !_is_sick && !_fresh_new)
        {
            return true;
        }
    }
    // if female
    else if (_gender == 2)
    {
        if (_age >= FEMALE_EAGLE_MATURITY && _age < FEMALE_EAGLE_UNFERTILITY_AGE && _gestation_month == 0 && !_is_sick && !_fresh_new)
        {
            return true;
        }
    }
    return false;
}

// ----- CHICKEN ------
Chicken::Chicken(int age, int gender) : IAnimal("Chicken", age, gender, CHICKEN_LIFESPAWN) {}

// will print the type, age and gender of the animal
void Chicken::showAnimal()
{
    cout << "Chicken, " << getGender() << ", " << getAge() << " month(s), " << endl;
}

// return true if animal is up for reproduction, false if not
bool Chicken::canReproduce()
{
    // if male
    if (_gender == 1)
    {
        if (_age >= ROOSTER_MATURITY && _age < ROOSTER_UNFERTILITY_AGE && !_is_sick && !_fresh_new)
        {
            return true;
        }
    }
    // if female
    else if (_gender == 2)
    {
        if (_age >= HEN_MATURITY && _age < HEN_UNFERTILITY_AGE && _gestation_month == 0 && !_is_sick && !_fresh_new)
        {
            return true;
        }
    }
    return false;
}