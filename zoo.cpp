#include <iostream>
#include <vector>
#include <typeinfo>
#include <random>
#include "zoo.h"
#include "ianimal.h"
#include "cage.h"
#include "config.h"

using namespace std;

int randint(int min,int max)
{
    random_device rd; // obtain a random number from hardware
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
void Zoo::monthlyUpdate()
{
    increaseAnimalAge();
    checkForEvent();
    checkForDisease();
    feedAnimals();
    if (population() == 0) {
        cout << ">> There are no animals in your zoo" << endl;
    } else {
        cout << ">> There are " << population() << " animal(s) in your zoo" << endl;
    }
    cout << "The zoo is up to date."
         << "\n"
         << endl;
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
void Zoo::feedAnimals()
{
    cout << ">> Animals have been fed." << endl;
}

// check if any accident happened
void Zoo::checkForEvent()
{
    int event = randint(1,100);
    if (event <= 1)
    {
        int type = randint(0,1);
        if (type == 0) {
            
            cout << ">> There was a fire in the zoo. (You loose 1 cage)" << endl;
            return;
        } else {
            cout << ">> Someone stole one of your animals. (You loose 1 animal)" << endl;
            return;
        }
    }
    event = randint(1,100);
    if (event <= 20)
    {
        cout << ">> There is some pests in your zoo. (You loose 10% of your seeds)" << endl;
        return;
    }
    event = randint(1,100);
    if (event <= 10)
    {
        cout << ">> The meats in your zoo is rotten. (You loose 20% of your meats)" << endl;
        return;
    }
    cout << ">> No event has occured this month." << endl;
}

// check if new disease has spread
void Zoo::checkForDisease()
{
    cout << ">> No new disease have been declared." << endl;
}

// add a cage to the zoo
void Zoo::addCage(Cage *newCage)
{
    _cage_list.push_back(newCage);
}

// add the animal to a cage, depending on the user's choice
void Zoo::addAnimal(IAnimal *newAnimal)
{
    cout << "In wich cage do you want to put it ?" << endl;
    showCageList();

    // if you have cages, you can choose to free it ; if you don't, it will escape
    if (_cage_list.size() > 0)
    {
        cout << "You can also free it by typing \"0\"" << endl;
    }
    else
    {
        cout << newAnimal->getName() << " ran away." << "\n" << endl;
        // delete newAnimal;
        return;
    }
    // take input
    int cage_index = -1;
    cin >> cage_index;

    // if it chose to free, kill it and break
    if (cage_index == 0)
    {
        newAnimal->escape();
        return;
    }

    // error handler
    while (cage_index < 1 || cage_index > _cage_list.size())
    {
        cout << "Wrong input. Try again : " << endl;
        cin >> cage_index;
    }
    _cage_list[cage_index - 1]->addAnimal(newAnimal);
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
void Zoo::showCageList()
{
    if (_cage_list.size() <= 0)
    {
        cout << "You don't have any cages. " << endl;
        return;
    }

    for (int i = 1; i <= _cage_list.size(); i++)
    {
        cout << i << ") " << _cage_list[i - 1]->getName() << " : " << _cage_list[i - 1]->numberOfAnimal() << "/" << _cage_list[i - 1]->getCapacity() << endl;
    }
}

// buy food depending on the user's choice (type & quantity). Cost money
void Zoo::buyFood(int *money)
{
    cout << "\n-- FOOD MARKET --\n"
         << endl;
    int quantity = 0;
    int action = 0;

    showFoodStock();

    cout << "1) Buy seeds\n2) Buy meat\n3) Exit\n"
         << endl;
    while (action != 3)
    {
        cout << "Action ?" << endl;
        cin >> action;
        while (action < 1 || action > 3)
        {
            cout << "Wrong input. Try again : " << endl;
            cin >> action;
        }
        if (action == 1 || action == 2)
        {
            cout << "How much ? " << endl;
            cin >> quantity;
            // error handler
            while (quantity < 1)
            {
                cout << "Wrong input. Try again :" << endl;
                cin >> quantity;
            }
            // if seed
            if (action == 1)
            {
                int price = SEED_PRICE * quantity;
                if (price > *money)
                {
                    cout << "You don't have enough money." << endl;
                }
                else
                {
                    _seed_stock += quantity;
                    *money -= price;
                    cout << "You succesfully bought " << quantity << " kg of seed.\n"
                         << endl;
                }
            }
            // if meat
            else
            {
                int price = MEAT_PRICE * quantity;
                if (price > *money)
                {
                    cout << "You don't have enough money." << endl;
                }
                else
                {
                    _meat_stock += quantity;
                    *money -= price;
                    cout << "You succesfully bought " << quantity << " kg of meat.\n"
                         << endl;
                }
            }
        }
        else
        {
            return;
        }
    }
}

// print how much food is in the zoo
void Zoo::showFoodStock()
{
    cout << "Food stock :" << endl;
    cout << "Meat : " << _meat_stock << "kg" << endl;
    cout << "Seed : " << _seed_stock << "kg"
         << "\n"
         << endl;
}

// update seed stock
void Zoo::newSeedStock(int change)
{
    _seed_stock += change;
}

// update meat stock
void Zoo::newMeatStock(int change)
{
    _meat_stock += change;
}

// find where the animal is in _cage_list and delete it from the zoo
void Zoo::withdrawAnimal(IAnimal* w_animal)
{
    for (auto cage : _cage_list)
    {
        vector<IAnimal*> animal_list = cage->getAnimalList();
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
    for (int i = 0; i<_cage_list.size(); i++)
    {
        if (_cage_list[i] == cage)
        {
            deleteCage(cage, i);
        }
    }
}

// retrieve animals based on type & age (works with IAnimal type)
vector<IAnimal*> Zoo::getAnimalListByAge(string type_name, int min_age, int max_age)
{
    vector<IAnimal*> result;
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
vector<IAnimal*> Zoo::getAnimalListByGender(string type_name, string gender)
{
    vector<IAnimal*> result;
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
vector<Cage*> Zoo::getCageList(string type, string status)
{
    vector<Cage*> result;
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
        cout << "Wrong parameters." << endl << endl;
    }
    return result;
}