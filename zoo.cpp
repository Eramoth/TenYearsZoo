#include <iostream>
#include <vector>
#include <typeinfo>
#include <random>
#include "functions.h"
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
    increaseAnimalAge();
    feedAnimals();
    checkForHealing();
    checkForDisease();
    overcrowdSickness();
    checkDeathByDisease();
    if (population() == 0)
    {
        cout << ">> There are no animals in your zoo" << endl;
    }
    else
    {
        cout << ">> There are " << population() << " animal(s) in your zoo" << endl;
    }
    cout << "The zoo is up to date."
         << endl
         << endl;
}

// check if animals have recovered from their past sickness
void Zoo::checkForHealing()
{
    for (auto cage : _cage_list)
    {
        for (auto animal : cage->getAnimalList())
        {
            if (animal->isSick())
            {
                int not_healing = randInt(0, 100 / HEALING_PROBA - 1);
                if (!not_healing)
                {
                    animal->getCured();
                }
            }
        }
    }
}

// check if animals have died from their sickness
void Zoo::checkDeathByDisease()
{
    for (auto cage : _cage_list)
    {
        for (auto animal : cage->getAnimalList())
        {
            if (animal->isSick())
            {
                int staying_healthy = randInt(0, 100 / SICKNESS_MORTALITY - 1);
                if (staying_healthy == 0)
                {
                    cout << animal->getName() << " died from its sickness. Maybe giving him alcohool to \"help him get better\" wasn't your brightest idea." << endl;
                    animal->kill(this);
                }
            }
        }
    }
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
    bool no_event = true;
    int event = randInt(1, 100);
    if (event <= 1)
    {
        int type = randInt(0, 1);
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
    event = randInt(1, 100);
    if (event <= 20)
    {
        pests();
        no_event = false;
    }
    event = randInt(1, 100);
    if (event <= 10)
    {
        avariateMeat();
        no_event = false;
    }

    if (no_event)
    {
        cout << ">> No event has occured this month." << endl;
    }
}

// check if new diseases have spread
void Zoo::checkForDisease()
{
    bool no_sickness = true;

    for (auto cage : _cage_list)
    {
        for (auto animal : cage->getAnimalList())
        {
            if (animal->getType() == "Tiger")
            {
                int stay_healthy = randInt(0, 100 / TIGER_SICKNESS_PROBA - 1);
                if (stay_healthy == 0)
                {
                    animal->getSick();
                }
                no_sickness = false;
            }
            else if (animal->getType() == "Eagle")
            {
                int stay_healthy = randInt(0, 100 / EAGLE_SICKNESS_PROBA - 1);
                if (stay_healthy == 0)
                {
                    animal->getSick();
                }
                no_sickness = false;
            }
            else if (animal->getType() == "Chicken")
            {
                int stay_healthy = randInt(0, 100 / CHICKEN_SICKNESS_PROBA - 1);
                if (stay_healthy == 0)
                {
                    animal->getSick();
                }
                no_sickness = false;
            }
            else
            {
                cout << "Type not supported." << endl;
            }
        }
    }
    // if no one get sick
    if (no_sickness)
    {
        cout << ">> No new disease have been declared." << endl;
    }
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
        cout << newAnimal->getName() << " ran away."
             << "\n"
             << endl;
        // delete newAnimal;
        return;
    }
    // take input
    int cage_index = -1;
    cin >> cage_index;

    // if it chose to free, kill it and break
    if (cage_index == 0)
    {
        newAnimal->escape(this);
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
    _seed_stock -= _seed_stock * SEED_LOSS;
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
    _meat_stock -= _meat_stock * MEAT_LOSS;
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

//retrieve animals based on their type
vector<IAnimal *> Zoo::getAnimalListByType(string type)
{
    vector<IAnimal *> result;
    for (auto cage : _cage_list)
    {
        for (auto animal : cage->getAnimalList())
        {
            if (animal->getType() == type)
                cout << "I'm in" << endl;
            result.push_back(animal);
        }
    }
    return result;
}

// retrieve animals based on max & min age
vector<IAnimal *> Zoo::getAnimalListByAge(int min_age, int max_age)
{
    vector<IAnimal *> result;
    for (auto cage : _cage_list)
    {
        for (auto animal : cage->getAnimalList())
        {
            if (animal->getAge() >= min_age && animal->getAge() <= max_age)
            {
                cout << "I'm in" << endl;
                result.push_back(animal);
            }
        }
    }
    return result;
}

// retrieve animals based on type & gender (work with IAnimal type)
vector<IAnimal *> Zoo::getAnimalListByGender(string gender)
{
    vector<IAnimal *> result;
    for (auto cage : _cage_list)
    {
        for (auto animal : cage->getAnimalList())
        {
            if (animal->getGender() == gender)
            {
                result.push_back(animal);
            }
        }
    }
    return result;
}

// return a vector of all the animals in the cages of the zoo
vector<IAnimal*> Zoo::getEveryAnimalList()
{
    vector<IAnimal*> result;
    for (auto cage : _cage_list)
    {
        for (auto animal : cage->getAnimalList())
        {
            result.push_back(animal);
        }
    }
    return result;
}

// return a vector of Cage*
vector<Cage*> Zoo::getCageList()
{
    return _cage_list;
}

// return a vector of Cage*, depending on their type and if they are empty or full
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

// delete a random cage and all of its animals
void Zoo::onFire()
{
    cout << ">> There was a fire in the zoo. (You lost 1 cage and all of its animals)" << endl;
    int cage_lost = randInt(0, _cage_list.size());
    deleteCage(_cage_list[cage_lost]);
}

// delete a random animal from a random cage
void Zoo::stolenAnimal()
{
    vector<IAnimal *> openedCage = _cage_list[randInt(0, _cage_list.size() - 1)]->getAnimalList();
    IAnimal *stolenAnimal = openedCage[randInt(0, openedCage.size())];
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
            if (randInt(0, 1))
            {
                cage->setOvercrowdDeath(this);
            }
        }
    }
}
