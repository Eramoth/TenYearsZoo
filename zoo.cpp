#include <iostream>
#include <vector>
#include <conio.h>
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
    res += "The zoo is up to date.\n";
    return res;
}

// feed the animals
string Zoo::feedAnimals()
{
    return ">> The animals are fed.\n";
}

// check if any accident happened
string Zoo::checkForEvent()
{
    int event = randint(1,100);
    if (event <= 1)
    {
        int type = randint(0,1);
        if (type == 0) {
            
            return ">> There was a fire in the zoo. (You loose 1 cage)\n";
        } else {
            return">> Someone stole one of your animals. (You loose 1 animal)\n";
        }
    }
    event = randint(1,100);
    if (event <= 20)
    {
        return ">> There is some pests in your zoo. (You loose 10% of your seeds)\n";
    }
    event = randint(1,100);
    if (event <= 10)
    {
        return ">> The meats in your zoo is rotten. (You loose 20% of your meats)\n";
    }
    return ">> No event has occured this month.\n";
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
                        newAnimal->escape();
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
        cout << newAnimal->getName() << " ran away." << "\n" << endl;
        // delete newAnimal;
        return;
    }
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
    _cage_list.push_back(_cage_list[cage_idx]);
}