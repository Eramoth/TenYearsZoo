#include <iostream>
#include <vector>
#include "zoo.h"
#include "ianimal.h"
#include "cage.h"
#include "config.h"

using namespace std;

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
    checkForEvent();
    checkForDisease();
    feedAnimals();
    cout << "There are " << population() << " animal(s) in your zoo." << endl;
    cout << "Zoo is up to date."
         << "\n"
         << endl;
}

// feed the animals
void Zoo::feedAnimals()
{
    cout << "Animals have been fed." << endl;
}

// check if any accident happened
void Zoo::checkForEvent()
{
    cout << "No event has occured this month." << endl;
}

// check if new disease has spread
void Zoo::checkForDisease()
{
    cout << "No new disease have been declared." << endl;
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

// delete the animal from the zoo
void Zoo::withdrawAnimal(IAnimal* w_animal)
{
    for (auto cage : _cage_list)
    {
        for (auto animal : cage->getAnimalList())
        {
            if (animal == w_animal)
            {
                cout << animal->getName() << " has been withdrawed from its cage." << endl;
                return;
            }
        }
    }
    cout << "There's no such animal in this Zoo." << endl;
}

void Zoo::killAnimal(IAnimal *animal)
{
    withdrawAnimal(animal);
    delete animal;
}