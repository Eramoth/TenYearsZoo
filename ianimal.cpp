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
    _gestation_month = 0;
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
    _fresh_new = false;
    return _age;
}

// return true if sick, false if healthy
bool IAnimal::isSick()
{
    return _is_sick;
}

// return true if dead, false if alive
bool IAnimal::isDead()
{
    return _is_dead;
}

// set death tag
void IAnimal::setDeathTag()
{
    _is_dead = true;
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

void IAnimal::setCured()
{
    _is_sick = false;
    cout << getName() << "'s sickness got cured, and he even kept one of it's leg healthy !" << endl;
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
        if (_age >= MALE_TIGER_MATURITY && _age < MALE_TIGER_UNFERTILITY_AGE && !_is_sick && !_fresh_new)
        {
            return true;
        }
    }
    // if female
    else if (_gender == 2)
    {
        if (_age >= FEMALE_TIGER_MATURITY && _age < FEMALE_TIGER_UNFERTILITY_AGE && _gestation_month == 0 && !_is_sick && !_fresh_new)
        {
            return true;
        }
    }
    return false;
}

// feed the animals depending on if there are pray in the cage and if they ahev enough to eat
void Tiger::feedAnimal(Cage* cage, Zoo* zoo)
{
    // if there are pray in the cage, eat it
    if (cage->hasChicken() != -1)
    {
        int index = cage->hasChicken();
        vector<IAnimal*> animals = cage->getAnimalList();
        animals[index]->setDeathTag();
        _is_hungry = false;
        return;
    }
    else if (cage->hasEagle() != -1)
    {
        int index = cage->hasEagle();
        vector<IAnimal*> animals = cage->getAnimalList();
        animals[index]->setDeathTag();
        _is_hungry = false;
        return;
    }

    // else, check how much food is needed
    float food_to_eat;
    if (_gender == 1)
    {
        food_to_eat = MALE_TIGER_MEAL;
    }
    else
    {
        food_to_eat = FEMALE_TIGER_MEAL;
    }
    // check if zoo has enough food, then update
    if (food_to_eat <= zoo->getMeatStock())
    {
        _is_hungry = false;
        zoo->newMeatStock(-food_to_eat);
        return;
    }
    else
    {
        zoo->newMeatStock(-zoo->getMeatStock());
        if (_is_hungry)
        {
            kill(zoo);
            return;
        }
        else
        {
            _is_hungry = true;
        }
    }
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

void Eagle::feedAnimal(Cage* cage, Zoo* zoo)
{
    // if there are pray in the cage, eat it
    if (cage->hasChicken() != -1)
    {
        int index = cage->hasChicken();
        vector<IAnimal*> animals = cage->getAnimalList();
        animals[index]->setDeathTag();
        _is_hungry = false;
        return;
    }

    // else, check how much food is needed
    float food_to_eat;
    if (_gender == 1)
    {
        food_to_eat = MALE_EAGLE_MEAL;
    }
    else
    {
        food_to_eat = FEMALE_EAGLE_MEAL;
    }
    // check if zoo has enough food
    if (food_to_eat <= zoo->getMeatStock())
    {
        _is_hungry = false;
        zoo->newMeatStock(-food_to_eat);
        return;
    }
    else
    {
        zoo->newMeatStock(-zoo->getMeatStock());
        if (_is_hungry)
        {
            kill(zoo);
        }
        else
        {
            _is_hungry = true;
        }
    }
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

void Chicken::feedAnimal(Cage* cage, Zoo* zoo)
{
    // else, check how much food is needed
    float food_to_eat;
    if (_gender == 1)
    {
        food_to_eat = ROOSTER_MEAL;
    }
    else
    {
        food_to_eat = HEN_MEAL;
    }
    // check if zoo has enough food
    if (food_to_eat <= zoo->getSeedStock())
    {
        _is_hungry = false;
        zoo->newSeedStock(-food_to_eat);
        return;
    }
    // if not, animal is hungry, and if it was already, kill it
    else
    {
        zoo->newMeatStock(-zoo->getSeedStock());
        if (_is_hungry)
        {
            kill(zoo);
            return;
        }
        else
        {
            _is_hungry = true;
        }
    }
}