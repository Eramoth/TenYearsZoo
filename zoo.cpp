#include <iostream>
#include <vector>
#include <conio.h>
#include <typeinfo>
#include <random>
#include "zoo.h"
#include "ianimal.h"
#include "cage.h"
#include "config.h"

using namespace std;

int randint(int min, int max)
{
    random_device rd;  // obtain a random number from hardware
    mt19937 gen(rd()); // seed the generator
    uniform_int_distribution<> distr(min, max);
    return distr(gen);
}

Zoo::Zoo()
{
    _meat_stock = 10;
    _seed_stock = 20;
    cout << "Congratulation ! You have built your own zoo ! Now, you have to fill it with animals." << endl;
}

Zoo::~Zoo()
{
    cout << "Zoo destroyed." << endl;
}

// structure and call everything that can happen between two month
string Zoo::monthlyUpdate()
{
    string res = checkForEvent();
    res += checkForDisease();
    res += feedAnimals();
    if (population() == 0) {
        res += ">> There are no animals in your zoo\n";
    } else {
        res += ">> There are " + to_string(population()) + " animal(s) in your zoo\n";
    }
    increaseAnimalAge();
    overcrowdSickness();
    if (population() == 0)
    {
        cout << ">> There are no animals in your zoo" << endl;
    }
    else
    {
        cout << ">> There are " << population() << " animal(s) in your zoo" << endl;
    }
    res += "The zoo is up to date.\n";
    return res;
}

// increase age of each animal
void Zoo::increaseAnimalAge()
{
    for (auto cage : _cage_list)
    {
        for (auto animal : cage->getAnimalList())
        {
            animal->increaseAge(this);
        }
    }
}

// feed the animals
string Zoo::feedAnimals()
{
    return ">> The animals are fed.\n";
}

// check if any accident happened
string Zoo::checkForEvent()
{
    bool no_event = true;
    int event = randint(1, 100);
    if (event <= 1)
    {
        int type = randint(0, 1);
        if (type == 0)
        {
            onFire();
            no_event = false;
        }
        else
        {
            stolenAnimal();
            no_event = false;
        }
    }
    event = randint(1, 100);
    if (event <= 20)
    {
        pests();
        no_event = false;
    }
    event = randint(1, 100);
    if (event <= 10)
    {
        avariateMeat();
        no_event = false;
    }

    if (no_event)
    {
       return ">> No event has occured this month.\n";
    }
}

// check if new disease has spread
string Zoo::checkForDisease()
{
    return ">> No new disease have been declared.\n";
}

// add a cage to the zoo
void Zoo::addCage(Cage *newCage)
{
    _cage_list.push_back(newCage);
}

// add the animal to a cage, depending on the user's choice
void Zoo::addAnimal(IAnimal *newAnimal)
{
    int choice = 1;
    int alpha = 0;
    if (_cage_list.size() > 0)
        {
            while(true)
            {
                int maxIndex = 10;
            if (_cage_list.size() - alpha * 10 < 10)
            {
                maxIndex = _cage_list.size() - alpha * 10;
            }
                system("cls");
                cout << "In wich cage do you want to put it ?" << endl;
                showCageList(choice,alpha,maxIndex);
                if (alpha * 10 + maxIndex >= _cage_list.size() && choice == maxIndex + 1){cout << "> Free animal" << endl;}
                else if (choice == maxIndex + 2) {cout << "> Free animal" << endl;}
                else {cout << "  Free animal" << endl;}

                int key = _getch();
                if (key == 72)
                {
                    if (alpha != 0 && choice == 0) {continue;}
                    if (choice == 1 && alpha == 0) {continue;}
                    else {choice -= 1;}
                }

                else if (key == 80)
                {
                    if (alpha * 10 + maxIndex >= _cage_list.size() && choice == maxIndex + 1) {continue;}
                    if (choice == maxIndex + 2) {continue;}
                    else {choice += 1;}
                }

                else if (key == 27)
                {
                    cout << ">>> You have quit the game." << endl;
                    exit(0);
                }

                else if (key == 13)
                {
                    if (choice == maxIndex + 2 || (alpha * 10 + maxIndex >= _cage_list.size() && choice == maxIndex + 1))
                    {
                        newAnimal->escape(this);
                        return;
                    }
                    if (choice == 0)
                    {
                        alpha -= 1;
                        choice = 10;
                        continue;
                    }
                    if (choice == maxIndex + 1)
                    {
                        alpha += 1;
                        choice = 1;
                        continue;
                    }
                    _cage_list[choice + alpha - 1]->addAnimal(newAnimal);
                    return;
                }
            }
        }
    // if you have cages, you can choose to free it ; if you don't, it will escape
    else
    {
        cout << newAnimal->getName() << " ran away."
             << "\n"
             << endl;
        // delete newAnimal;
        return;
    }
}

vector<Cage*> Zoo::getCageListByType(string type)
{
    vector<Cage*> res;
    for (int i = 0; i < _cage_list.size(); i++)
    {
        if (_cage_list[i]->getType() == type)
        {
            res.push_back(_cage_list[i]);
        }
    }
    return res;
}

void Zoo::addSeeds(int nb)
{
    _seed_stock += nb;
}

void Zoo::addMeats(int nb)
{
    _meat_stock += nb;
}

// return the number of animals in the zoo
int Zoo::population()
{
    int result = 0;
    for (auto cage : _cage_list)
    {
        result += cage->numberOfAnimal();
    }
    return result;
}

// will print all the cage's name, number of animals and capacity
void Zoo::showCageList(int index,int alpha,int maxIndex)
{
    if (_cage_list.size() <= 0)
    {
        cout << "You don't have any cages. " << endl;
        return;
    }

    if (alpha != 0)
    {
        if (index == 0) {cout << "> See Less" << endl;}
        else {cout << "  See Less" << endl;}
    }
    for (int i = 1; i <= maxIndex; i++)
    {
        if (index == i)
        {
            cout << "> " << _cage_list[alpha * 10 + i - 1]->getName() << " : " << _cage_list[alpha * 10 + i - 1]->numberOfAnimal() << "/" << _cage_list[alpha * 10 + i - 1]->getCapacity() << endl;
        } else {
            cout << "  " << _cage_list[alpha * 10 + i - 1]->getName() << " : " << _cage_list[alpha * 10 + i - 1]->numberOfAnimal() << "/" << _cage_list[alpha * 10 + i - 1]->getCapacity() << endl;
        }
    }
    if (alpha * 10 + maxIndex < _cage_list.size())
    {
        if (index == maxIndex + 1) {cout << "> See More" << endl;}
        else {cout << "  See More" << endl;}
    }
}

// print how much food is in the zoo
void Zoo::showFoodStock()
{
    cout << "Food stock :" << endl;
    cout << "Meat : " << _meat_stock << "kg" << endl;
    cout << "Seed : " << _seed_stock << "kg"
         << endl
         << endl;
}

// update seed stock
void Zoo::newSeedStock(int change)
{
    _seed_stock += change;
}

// seed loss due to pests in the zoo
void Zoo::pests()
{
    _seed_stock -= _seed_stock*SEED_LOSS;
    cout << ">> There are some pests in your zoo. (You lost 10% of your seeds)" << endl
         << "New seed stock : " << _seed_stock << endl;
}

// update meat stock
void Zoo::newMeatStock(int change)
{
    _meat_stock += change;
}

// meat loss due to avariate meat
void Zoo::avariateMeat()
{
    _meat_stock -= _meat_stock*MEAT_LOSS;
    cout << ">> The meat in your zoo has rotten. (You lost 20% of your meat)" << endl
         << "New meat stock : " << _meat_stock << endl;
}

// find where the animal is in _cage_list and delete it from the zoo
void Zoo::withdrawAnimal(IAnimal *w_animal)
{
    for (auto cage : _cage_list)
    {
        vector<IAnimal *> animal_list = cage->getAnimalList();
        for (auto animal : cage->getAnimalList())
        {
            if (animal == w_animal)
            {
                cout << w_animal->getName() << " has been withdrawed form its cage." << endl;
                cage->freeAnimal(w_animal);
                return;
            }
        }
    }
    cout << "There's no such animal in this Zoo." << endl;
}

// delete animal, withdraw it from it's cage, and cry a bit
void Zoo::killAnimal(IAnimal *animal)
{
    withdrawAnimal(animal);
    cout << animal->getName() << " has been killed :(((((" << endl;
    delete animal;
}

// delete a cage and all the animals in it, and remove it from _cage_list
void Zoo::deleteCage(Cage *cage, int cage_idx)
{
    for (auto animal : cage->getAnimalList())
    {
        killAnimal(animal);
    }
    _cage_list.erase(_cage_list.begin() + cage_idx);
}

// surcharge when you can't have index
void Zoo::deleteCage(Cage *cage)
{
    for (int i = 0; i < _cage_list.size(); i++)
    {
        if (_cage_list[i] == cage)
        {
            deleteCage(cage, i);
        }
    }
}

// retrieve animals based on type & age (works with IAnimal type)
vector<IAnimal *> Zoo::getAnimalListByAge(string type_name, int min_age, int max_age)
{
    vector<IAnimal *> result;
    for (auto cage : _cage_list)
    {
        for (auto animal : cage->getAnimalList())
        {
            string animal_type = typeid(animal).name();
            if (animal_type.find(type_name) && animal->getAge() >= min_age && animal->getAge() <= max_age)
            {
                cout << "I'm in" << endl;
                result.push_back(animal);
            }
        }
    }
    return result;
}

// retrieve animals based on type & gender (work with IAnimal type)
vector<IAnimal *> Zoo::getAnimalListByGender(string type_name, string gender)
{
    vector<IAnimal *> result;
    for (auto cage : _cage_list)
    {
        for (auto animal : cage->getAnimalList())
        {
            if (typeid(animal).name() == type_name && animal->getGender() == gender)
            {
                result.push_back(animal);
            }
        }
    }
    return result;
}

// return a vector of Cage*, depending on their type and if they are empty or full ;
// pass "any" as parameters to get everything
vector<Cage *> Zoo::getCageList(string type, string status)
{
    vector<Cage *> result;
    // any type of cage
    if (type == "any")
    {
        if (status == "empty")
        {
            for (auto cage : _cage_list)
            {
                if (cage->getAnimalList().size() == 0)
                {
                    result.push_back(cage);
                }
            }
        }
        else if (status == "full")
        {
            for (auto cage : _cage_list)
            {
                if (cage->getAnimalList().size() >= cage->getCapacity())
                {
                    result.push_back(cage);
                }
            }
        }
        else if (status == "any")
        {
            return _cage_list;
        }
    }
    else if (type == "Tiger")
    {
        if (status == "empty")
        {
            for (auto cage : _cage_list)
            {
                if (cage->getType() == "Tiger" && cage->isEmpty())
                {
                    result.push_back(cage);
                }
            }
        }
        else if (status == "full")
        {
            for (auto cage : _cage_list)
            {
                if (cage->getType() == "Tiger" && cage->isOvercrowded())
                {
                    result.push_back(cage);
                }
            }
        }
        else if (status == "any")
        {
            for (auto cage : _cage_list)
            {
                if (cage->getType() == "Tiger")
                {
                    result.push_back(cage);
                }
            }
        }
    }
    else if (type == "Eagle")
    {
        if (status == "empty")
        {
            for (auto cage : _cage_list)
            {
                if (cage->getType() == "Eagle" && cage->isEmpty())
                {
                    result.push_back(cage);
                }
            }
        }
        else if (status == "full")
        {
            for (auto cage : _cage_list)
            {
                if (cage->getType() == "Eagle" && cage->isOvercrowded())
                {
                    result.push_back(cage);
                }
            }
        }
        else if (status == "any")
        {
            for (auto cage : _cage_list)
            {
                if (cage->getType() == "Eagle")
                {
                    result.push_back(cage);
                }
            }
        }
    }
    else if (type == "Chicken")
    {
        if (status == "empty")
        {
            for (auto cage : _cage_list)
            {
                if (cage->getType() == "Chicken" && cage->isEmpty())
                {
                    result.push_back(cage);
                }
            }
        }
        else if (status == "full")
        {
            for (auto cage : _cage_list)
            {
                if (cage->getType() == "Chicken" && cage->isOvercrowded())
                {
                    result.push_back(cage);
                }
            }
        }
        else if (status == "any")
        {
            for (auto cage : _cage_list)
            {
                if (cage->getType() == "Chicken")
                {
                    result.push_back(cage);
                }
            }
        }
    }
    else
    {
        cout << "Wrong parameters." << endl
             << endl;
    }
    return result;
}

void Zoo::onFire()
{
    cout << ">> There was a fire in the zoo. (You lost 1 cage and all of its animals)" << endl;
    int cage_lost = randint(0, _cage_list.size());
    deleteCage(_cage_list[cage_lost]);
}

// delete a random animal from a random cage
void Zoo::stolenAnimal()
{
    vector<IAnimal *> openedCage = _cage_list[randint(0, _cage_list.size() - 1)]->getAnimalList();
    IAnimal *stolenAnimal = openedCage[randint(0, openedCage.size())];
    cout << ">> " << stolenAnimal->getName() << " has been stolen. You lost 1 animal" << endl;
    killAnimal(stolenAnimal);
}

// check if each cage is overcrowded, then check if sick
void Zoo::overcrowdSickness()
{
    for (auto cage : _cage_list)
    {
        if (cage->isOvercrowded())
        {
            cage->setOvercrowdSickness();
            if (randint(0, 1))
            {
                cage->setOvercrowdDeath(this);
            }
        }
    }
}


