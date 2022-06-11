// THINGS TO CHANGE
// L.470 : getCageList()

#include <iostream>
#include <vector>
#include <conio.h>
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
void Zoo::monthlyUpdate(string* story, int month, int* money)
{
    checkForEvent(story);
    checkForDisease(story);
    overcrowdSickness(story);
    checkDeathByDisease(story);
    massReproduce(story);
    checkForBirths(story);
    checkForTurism(story, month, money);
    feedAnimals(story);
    checkForHealing(story);
    increaseAnimalAge();
    if (population() == 0) {
        *story += ">> There are no animals in your zoo\n";
    } else {
        *story += ">> There are " + to_string(population()) + " animal(s) in your zoo\n";
    }
    *story += "The zoo is up to date.\n";
}

// give money depending on how much turist came to your zoo
void Zoo::checkForTurism(string* story, int month, int *money)
{
    // init
    int tickets_number = 0;
    vector<IAnimal *> animals = getEveryAnimalList();
    bool high_season = false;
    if (month >= HIGH_SEASON_START && month < LOW_SEASON_START)
    {
        high_season = true;
    }
    // get money
    for (auto animal : animals)
    {
        if (animal->getType() == "Tiger")
        {
            if (high_season)
            {
                tickets_number += TIGER_HIGH_VISITOR;
            }
            else
            {
                tickets_number += TIGER_LOW_VISITOR;
            }
        }
        else if (animal->getType() == "Eagle")
        {
            if (high_season)
            {
                tickets_number += EAGLE_HIGH_VISITOR;
            }
            else
            {
                tickets_number += EAGLE_LOW_VISITOR;
            }
        }
        else if (animal->getType() == "Chicken")
        {
            if (high_season)
            {
                tickets_number += CHICKEN_HIGH_VISITOR;
            }
            else
            {
                tickets_number += CHICKEN_LOW_VISITOR;
            }
        }
        else
        {
            cout << __LINE__ << "Invalid animal type." << endl;
        }
    }
    *money+=tickets_number*TICKET_PRICE;
    *story += ">> Some turists came to your zoo, and where really happy !\n";
}
// check if animals have recovered from their past sickness
void Zoo::checkForHealing(string* story)
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
                    *story += ">> " + animal->getName() + " has been cured, and he even kept one of it's leg healthy !\n";
                    animal->setCured();
                }
            }
        }
    }
}

// check if animals have died from their sickness
void Zoo::checkDeathByDisease(string* story)
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
                    *story += ">> " + animal->getName() + " died from its sickness. Maybe giving them alcohool to \"help them get better\" wasn't your brightest idea.\n";
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

void Zoo::massReproduce(string* story)
{
    int count = 0;
    for (auto cage : _cage_list)
    {
        for (auto animal : cage->getAnimalList())
        {
            if (animal->getGender() == "male" && animal->canReproduce())
            {
                for (auto animal2 : cage->getAnimalList())
                {
                    if (animal == animal2)
                    {
                        continue;
                    }
                    if (animal2->getGender() == "female" && animal2->canReproduce() && animal->getType() == animal2->getType() && animal->getType() == "Eagle" && animal2->getPartner() == animal)
                    {
                        animal2->setPregnancy(true);
                        count++;
                        continue;
                    }
                    if (animal2->getGender() == "female" && animal2->canReproduce() && animal->getType() == animal2->getType() && animal->getType() == "Eagle" && animal2->getPartner() == NULL && animal->getPartner() == NULL)
                    {
                        animal2->setPregnancy(true);
                        animal->setPartner(animal2);
                        animal2->setPartner(animal);
                        count++;
                        continue;
                    }
                    if (animal2->getGender() == "female" && animal2->canReproduce() && animal->getType() == animal2->getType())
                    {
                        animal2->setPregnancy(true);
                        count++;
                        continue;
                    }
                }
            }
        }
    }
    *story += ">> " + to_string(count) + " animals got pregnant\n";
}

// feed the animals
void Zoo::feedAnimals(string* story)
{
        for (auto cage : _cage_list)
    {
        for (auto animal : cage->getAnimalList())
        {
            if (!animal->isDead()) {animal->feedAnimal(cage, this);}
        }
    }
    // if some animals has been eaten, delete them
    for (auto animal : getEveryAnimalList())
    {
        if (animal->isDead())
        {
            *story+= ">> " + animal->getName() + " has been eaten. Maybe next time you wnon't try to help them make friend with their natural predator\n";
            animal->kill(this);
        }
    }
    *story += ">> Animals have been fed.\n";
}

// check if any accident happened
void Zoo::checkForEvent(string* story)
{
    int event = randInt(1, 100);
    if (event <= 1)
    {
        int type = randInt(0, 1);
        if (type == 0)
        {
            onFire(story);
        }
        else
        {
            stolenAnimal(story);
        }
    }
    event = randInt(1, 100);
    if (event <= 20)
    {
        pests(story);
    }
    event = randInt(1, 100);
    if (event <= 10)
    {
        avariateMeat(story);
    }
    *story += ">> No event has occured this month.\n";
}

// check if new diseases have spread
void Zoo::checkForDisease(string* story)
{
    bool no_sickness = true;

    for (auto cage : _cage_list)
    {
        for (auto animal : cage->getAnimalList())
        {
            int sickness_proba;
            if (animal->getType() == "Tiger")
            {
                sickness_proba = TIGER_SICKNESS_PROBA;
            }
            else if (animal->getType() == "Eagle")
            {
                sickness_proba = EAGLE_SICKNESS_PROBA - 1;
            }
            else if (animal->getType() == "Chicken")
            {
                sickness_proba = CHICKEN_SICKNESS_PROBA - 1;
            }
            else
            {
                cout << "Type not supported." << endl;
            }

            int stay_healthy = randInt(0, 100 / sickness_proba - 1);
            if (stay_healthy == 0)
            {
                animal->setSick();
                *story += ">> " + animal->getName() + " got sick.\n";
            }
            no_sickness = false;
        }
    }
    // if no one get sick
    if (no_sickness)
    {
        *story += ">> No new disease have been declared.\n";
    }
}

void Zoo::checkForBirths(string* story)
{
    int tigerBirths = 0;
    int eagleBirths = 0;
    int chickenBirths = 0;
    int tigerMortality = 0;
    int eagleMortality = 0;
    int chickenMortality = 0;
    for (auto cage : _cage_list)
    {
        for (auto animal : cage->getAnimalList())
        {
            if (animal->isPregnant() && animal->getGestationMonth() >= TIGER_GESTATION && animal->getType() == "Tiger")
            {
                int odd = randInt(0, 100);
                if (odd <= TIGER_CHILD_MORTALITY)
                {
                    tigerMortality++;
                }
                else
                {
                    animal->setPregnancy(false);
                    int sex = randInt(0,1);
                    Tiger *newAnimal = new Tiger(0, sex+1);
                    addAnimal(newAnimal);
                    tigerBirths++;
                }
            }
            if (animal->isPregnant() && animal->getGestationMonth() == EAGLE_GESTATION_ && animal->getType() == "Eagle")
            {
                int odd = randInt(0, 100);
                if (odd <= EAGLE_CHILD_MORTALITY)
                {
                    eagleMortality++;
                }
                else
                {
                    animal->setPregnancy(false);
                    int sex = randInt(0,1);
                    Eagle *newAnimal = new Eagle(0,sex+1);
                    addAnimal(newAnimal);
                    eagleBirths++;
                }
            }
            if (animal->isPregnant() && animal->getGestationMonth() == CHICKEN_GESTATION && animal->getType() == "Chicken")
            {
                int odd = randInt(0, 100);
                if (odd <= CHICKEN_CHILD_MORTALITY)
                {
                    chickenMortality++;
                }
                else
                {
                    animal->setPregnancy(false);
                    int sex = randInt(0,1);
                    Chicken *newAnimal = new Chicken(0,sex+1);
                    addAnimal(newAnimal);
                    chickenBirths++;
                }
            }
        }
    }
    if (tigerBirths != 0) {
        *story += ">> " + to_string(tigerBirths) + " tigers was born this month.\n";
    }
    if (eagleBirths != 0) {
        *story += ">> " + to_string(eagleBirths) + " eagles was born this month.\n";
    }
    if (chickenBirths != 0) {
        *story += ">> " + to_string(chickenBirths) + " chickens was born this month.\n";
    }
    if (tigerMortality != 0) {
        *story += ">> " + to_string(tigerMortality) + " tigers was born this month. Wait... Nevermind they didn't make it\n";
    }
    if (eagleMortality != 0) {
        *story += ">> " + to_string(eagleMortality) + " eagles was born this month. Wait... Nevermind they didn't make it\n";
    }
    if (chickenMortality != 0) {
        *story += ">> " + to_string(chickenMortality) + " chickens was born this month. Wait... Nevermind they didn't make it\n";
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
    int choice = 1;
    int alpha = 0;
    if (_cage_list.size() > 0)
    {
        while (true)
        {
            int maxIndex = 10;
            if (_cage_list.size() - alpha * 10 < 10)
            {
                maxIndex = _cage_list.size() - alpha * 10;
            }
            system("cls");
            cout << "In wich cage do you want to put it ?" << endl;
            showCageList(choice, alpha, maxIndex);
            if (alpha * 10 + maxIndex >= _cage_list.size() && choice == maxIndex + 1)
            {
                cout << "> Free animal" << endl;
            }
            else if (choice == maxIndex + 2)
            {
                cout << "> Free animal" << endl;
            }
            else
            {
                cout << "  Free animal" << endl;
            }

            int key = _getch();
            if (key == 72)
            {
                if (alpha != 0 && choice == 0)
                {
                    continue;
                }
                if (choice == 1 && alpha == 0)
                {
                    continue;
                }
                else
                {
                    choice -= 1;
                }
            }

            else if (key == 80)
            {
                if (alpha * 10 + maxIndex >= _cage_list.size() && choice == maxIndex + 1)
                {
                    continue;
                }
                if (choice == maxIndex + 2)
                {
                    continue;
                }
                else
                {
                    choice += 1;
                }
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
void Zoo::showCageList(int index, int alpha, int maxIndex)
{
    if (_cage_list.size() <= 0)
    {
        cout << "You don't have any cages. " << endl;
        return;
    }

    if (alpha != 0)
    {
        if (index == 0)
        {
            cout << "> See Less" << endl;
        }
        else
        {
            cout << "  See Less" << endl;
        }
    }
    for (int i = 1; i <= maxIndex; i++)
    {
        if (index == i)
        {
            cout << "> " << _cage_list[alpha * 10 + i - 1]->getName() << " : " << _cage_list[alpha * 10 + i - 1]->numberOfAnimal() << "/" << _cage_list[alpha * 10 + i - 1]->getCapacity() << endl;
        }
        else
        {
            cout << "  " << _cage_list[alpha * 10 + i - 1]->getName() << " : " << _cage_list[alpha * 10 + i - 1]->numberOfAnimal() << "/" << _cage_list[alpha * 10 + i - 1]->getCapacity() << endl;
        }
    }
    if (alpha * 10 + maxIndex < _cage_list.size())
    {
        if (index == maxIndex + 1)
        {
            cout << "> See More" << endl;
        }
        else
        {
            cout << "  See More" << endl;
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
void Zoo::newSeedStock(float change)
{
    _seed_stock += change;
}

// seed loss due to pests in the zoo
void Zoo::pests(string* story)
{
    _seed_stock -= _seed_stock*SEED_LOSS;
    *story += ">> There are some pests in your zoo. (You lost 10% of your seeds)\nNew seed stock : " + to_string(_seed_stock) + "Kg \n";
}

// update meat stock
void Zoo::newMeatStock(float change)
{
    _meat_stock += change;
}

// meat loss due to avariate meat
void Zoo::avariateMeat(string* story)
{
    _meat_stock -= _meat_stock*MEAT_LOSS;
    *story += ">> The meat in your zoo has rotten. (You lost 20% of your meat)\nNew meat stock : " +to_string(_meat_stock)+ "Kg \n";
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

// return meat stock
float Zoo::getMeatStock()
{
    return _meat_stock;
}

float Zoo::getSeedStock()
{
    return _seed_stock;
}
// retrieve animals based on their type
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
vector<IAnimal *> Zoo::getEveryAnimalList()
{
    vector<IAnimal *> result;
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
vector<Cage *> Zoo::getCageList()
{
    return _cage_list;
}

/* return a vector of Cage*, depending on their
type and if they are empty or full
pass "any" as parameters to get everything */
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

void Zoo::onFire(string* story)
{
    int cage_lost = randInt(0, _cage_list.size());
    deleteCage(_cage_list[cage_lost]);
    *story += ">> There was a fire in the zoo. (You lost 1 cage and all of its animals)\n";
}

// delete a random animal from a random cage
void Zoo::stolenAnimal(string* story)
{
    vector<IAnimal *> openedCage = _cage_list[randInt(0, _cage_list.size() - 1)]->getAnimalList();
    IAnimal *stolenAnimal = openedCage[randInt(0, openedCage.size())];
    killAnimal(stolenAnimal);
    *story += ">> " + stolenAnimal->getName() + " has been stolen. You lost 1 animal\n";
}

// check if each cage is overcrowded, then check if sick
void Zoo::overcrowdSickness(string* story)
{
    string string = "";
    for (auto cage : _cage_list)
    {
        if (cage->isOvercrowded())
        {
            string += cage->setOvercrowdSickness() + "\n";
            if (randInt(0, 1))
            {
                string += cage->setOvercrowdDeath(this) + "\n";
            }
        }
    }
    *story += string;
}
