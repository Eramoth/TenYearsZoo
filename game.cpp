#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include <conio.h>
#include "functions.h"
#include "game.h"
#include "zoo.h"
#include "config.h"

using namespace std;

int Game::getMonth()
{
    return _currentMonth;
}

int Game::getYear()
{
    return _currentYear;
}

Zoo *Game::getZoo()
{
    return _zoo;
}

// run at the start, return true for new game, false to close the app
void Game::startGame()
{
    cout << "*---------------------------------*" << endl;
    cout << "| Welcome to ZOO SIMULATOR 3000 ! |" << endl;
    cout << "*---------------------------------*" << endl;
    _zoo = new Zoo();
    this_thread::sleep_for(std::chrono::seconds(2));
}

// set up some starter
void Game::setScenario()
{
    // add cages
    for (int i = 0; i<4; i++)
    {
        _zoo->addCage(new Cage("Tiger"));
        _zoo->addCage(new Cage("Eagle"));
        _zoo->addCage(new Cage("Chicken"));
    }
    // add tigers
    for (int i = 0; i<1; i++)
    {
        _zoo->addAnimal(new Tiger(60, 1));
        _zoo->addAnimal(new Tiger(60, 2));
    }
    // add eagles
    for (int i = 0; i<1; i++)
    {
        _zoo->addAnimal(new Eagle(60, 1));
        _zoo->addAnimal(new Eagle(60, 2));
    }
    // add chickens
    for (int i = 0; i<4; i++)
    {
        _zoo->addAnimal(new Chicken(50, 1));
        _zoo->addAnimal(new Chicken(50, 2));
    }
}

// date in full letters
string Game::parseDate()
{
    string date;
    switch (_currentMonth)
    {
    case 1:
        date = "JANUARY";
        break;
    case 2:
        date = "FEBRUARY";
        break;
    case 3:
        date = "MARCH";
        break;
    case 4:
        date = "APRIL";
        break;
    case 5:
        date = "MAY";
        break;
    case 6:
        date = "JUNE";
        break;
    case 7:
        date = "JULY";
        break;
    case 8:
        date = "AUGUST";
        break;
    case 9:
        date = "SEPTEMBER";
        break;
    case 10:
        date = "OCTOBER";
        break;
    case 11:
        date = "NOVEMBER";
        break;
    case 12:
        date = "DECEMBER";
        break;
    }

    date += ", YEAR " + to_string(_currentYear);
    return date;
}

// update the zoo
void Game::monthlyUpdate(string* story)
{
    _zoo->monthlyUpdate(story,_currentMonth, &_money);
}

// happy new year !
void Game::newYear()
{
    _currentMonth = 1;
    _currentYear += 1;
    cout << "Hapy New Year !" << endl;
}

// go to next month
void Game::nextTurn()
{
    _currentMonth += 1;
    if (_currentMonth > 12)
    {
        newYear();
    }
}

// update money
void Game::setMoney(int change)
{
    _money+=change;
}

int Game::getMoney()
{
    return _money;
}

// player actions during turn. Loop untill skip turn
void Game::menu(string update)
{
    int action = 0;
    while (1)
    {
        system("cls");
        cout << "\n----------------\n"
             << parseDate() << "\n"
             << endl;

        cout << update << endl;
        cout << "** Your Money : " << _money << " **"<< endl;
        cout << "You can do the following actions :" << endl;
        if (action == 0) {cout << "> Buy new animals" << endl;}
        else {cout << "  Buy new animals" << endl;}
        if (action == 1) {cout << "> Sell animals" << endl;}
        else {cout << "  Sell animals" << endl;}
        if (action == 2) {cout << "> Buy food" << endl;}
        else {cout << "  Buy food" << endl;}
        if (action == 3) {cout << "> Buy new cages" << endl;}
        else {cout << "  Buy new cages" << endl;}
        if (action == 4) {cout << "> Sell cages" << endl;}
        else {cout << "  Sell cages" << endl;}
        if (action == 5) {cout << "> End turn" << endl;}
        else {cout << "  End turn" << endl;}
        cout << "\nUse arrow keys to navigate and press enter to accept" << endl;
        int key = _getch();
        if (key == 72)
        {
            if (action == 0) {continue;}
            else {action -= 1;}
        }

        else if (key == 80)
        {
            if (action == 5) {continue;}
            else {action += 1;}
        }

        else if (key == 13)
        {
            switch (action+1)
            {
            case 1:
                buyAnimal();
                break;
            case 2:
                sellAnimalMenu();
                break;
            case 3:
                buyFood();
                break;
            case 4:
                buyCage();
                break;
            case 5 :
                sellCage();
                break;
            case 6:
                cout << "Turn ended." << endl;
                return;
            default:
                cout << ">>> Wrong input, try again." << endl;
                break;
            }
        }

        else if (key == 27)
        {
            cout << ">>> You have quit the game." << endl;
            exit(0);
        }
    }
}

// buy an animal and add it to the zoo
void Game::buyAnimal()
{
    int price = 0;
    int action = 1;
    string type = "";   
    int age = 0;
    int gender = 0;

    while (true)
    {
        // initialization
        int price = 0;
        string type = "";
        int age = 0;
        int gender = 0;

        system("cls");
        cout << "\n-- ANIMAL MARKET --" << endl;
        cout << "** Your Money : " << _money << " **\n"<< endl;
        showAnimalToBuy(action);
        int key = _getch();
        if (key == 72)
        {
            if (action == 1) {continue;}
            else {action -= 1;}
        }

        else if (key == 80)
        {
            if (action == 9) {continue;}
            else {action += 1;}
        }

        else if (key == 27)
        {
            cout << ">>> You have quit the game." << endl;
            exit(0);
        }

        else if (key == 13)
        {
        // define the animal depending on the player's choice
            switch (action)
            {
            case 1:
                type = "Tiger";
                age = 6;
                price = YOUNG_TIGER_BUY_PRICE;
                break;
            case 2:
                type = "Tiger";
                age = 48;
                price = ADULT_TIGER_BUY_PRICE;
                break;
            case 3:
                type = "Tiger";
                age = 168;
                price = OLD_TIGER_BUY_PRICE;
                break;
            case 4:
                type = "Eagle";
                age = 6;
                price = YOUNG_EAGLE_BUY_PRICE;
                break;
            case 5:
                type = "Eagle";
                age = 48;
                price = ADULT_EAGLE_BUY_PRICE;
                break;
            case 6:
                type = "Eagle";
                age = 168;
                price = OLD_EAGLE_BUY_PRICE;
                break;
            case 7:
                type = "Chicken";
                age = 6;
                gender = 2;
                price = YOUNG_HEN_BUY_PRICE;
                break;
            case 8:
                type = "Chicken";
                age = 6;
                gender = 1;
                price = YOUNG_ROOSTER_BUY_PRICE;
                break;
            case 9:
                cout << ">> Exited animal market."
                    << "\n"
                    << endl;
                return;
            default:
                cout << ">>> Wrong input, try again."
                    << "\n"
                    << endl;
                    //  this_thread::sleep_for(std::chrono::seconds(1));
                    continue;
            }

        if (_money < price)
        {
            cout << ">> You don't have enough money."
                 << endl
                 << endl;
                //  this_thread::sleep_for(std::chrono::seconds(1));
            continue;
        }
        else
        {
            _money -= price;
        }
                // if gender is not defined, define it (1 for male, 2 for female):
            int action2 = 0;
            while (action != 7 && action != 8)
            {
                system("cls");
                cout << "\n-- ANIMAL MARKET --" << endl;
                cout << "** Your Money : " << _money << " **\n"<< endl;
                showAnimalToBuy(action);
                cout << "Gender:" << endl;
                if (action2 == 0) {cout << "> Male" << endl;}
                else {cout << "  Male" << endl;}
                if (action2 == 1) {cout << "> Female" << endl;}
                else {cout << "  Female" << endl;}
                int key2 = _getch();
                if (key2 == 72)
                {
                    if (action2 == 0) {continue;}
                    else {action2 -= 1;}
                }

                else if (key2 == 80)
                {
                    if (action2 == 2) {continue;}
                    else {action2 += 1;}
                }

                else if (key2 == 27)
                {
                    cout << ">>> You have quit the game." << endl;
                    exit(0);
                }

                else if (key2 == 13)
                {
                    cout << endl;
                     // create the animal
                    if (type == "Tiger")
                    {
                        Tiger *newAnimal = new Tiger(age, action2+1);
                        _zoo->addAnimal(newAnimal);
                    }
                    else if (type == "Eagle")
                    {
                        Eagle *newAnimal = new Eagle(age, action2+1);
                        _zoo->addAnimal(newAnimal);
                    }
                    break;
                }
                }
                if (type == "Chicken")
                {
                    Chicken *newAnimal = new Chicken(age, gender);
                    _zoo->addAnimal(newAnimal);
                }
                cout << endl;
                this_thread::sleep_for(std::chrono::seconds(3));
            }
        }
}

// buy cages depending on player's choice, then add it to the zoo
void Game::buyCage()
{
    // show available items
    int action = 0;
    string type = "";
    int price = 0;
    while (true)
    {
        system("cls");
        cout << "\n-- CAGE MARKET --\n" << endl;
        cout << "** Your Money : " << _money << " **\n" << endl;
        cout << ">> You have " << _zoo->getCageList("Tiger","any").size() << " tiger cages." << endl;
        cout << ">> You have " << _zoo->getCageList("Eagle","any").size() << " eagle cages." << endl;
        cout << ">> You have " << _zoo->getCageList("Chicken","any").size() << " chicken cages." << endl;
        cout << "Cages available :\n" << endl;
        if (action == 0) {cout << "> Tiger cage : " << TIGER_CAGE_BUY_PRICE << endl;}
        else {cout << "  Tiger cage : " << TIGER_CAGE_BUY_PRICE << endl;}
        if (action == 1) {cout << "> Eagle cage : " << EAGLE_CAGE_BUY_PRICE << endl;}
        else {cout << "  Eagle cage : " << EAGLE_CAGE_BUY_PRICE << endl;}
        if (action == 2) {cout << "> Chicken cage : " << CHICKEN_CAGE_BUY_PRICE << endl;}
        else {cout << "  Chicken cage : " << CHICKEN_CAGE_BUY_PRICE << endl;}
        if (action == 3) {cout << "> Exit" << endl;}
        else {cout << "  Exit" << endl;}

        int key = _getch();
        if (key == 72)
        {
            if (action == 0) {continue;}
            else {action -= 1;}
        }

        else if (key == 80)
        {
            if (action == 3) {continue;}
            else {action += 1;}
        }

        else if (key == 27)
        {
            cout << ">>> You have quit the game." << endl;
            exit(0);
        }

        else if (key == 13)
        {
            cout << endl;
            switch (action+1)
            {
            case 1:
                type = "Tiger";
                price = TIGER_CAGE_BUY_PRICE;
                break;
            case 2:
                type = "Eagle";
                price = EAGLE_CAGE_BUY_PRICE;
                break;
            case 3:
                type = "Chicken";
                price = CHICKEN_CAGE_BUY_PRICE;
                break;
            case 4:
                cout << "Exited cage market.\n"
                    << endl;
                return;
            default:
                cout << "Wrong input, try again." << endl;
                break;
            }
            if (type != "" && _money >= price)
            {
                Cage *newCage = new Cage(type);
                _zoo->addCage(newCage);
                _money -= price;
            }
            else if (_money < price)
            {
                cout << "You don't have enough money." << endl;
            }
            this_thread::sleep_for(std::chrono::seconds(1));
        }
    }
}

// buy food depending on the user's choice (type & quantity). Cost money
void Game::buyFood()
{
    int quantity = 0;
    int action = 0;
    int choice = 0;
    while (true)
    {
        system("cls");
        cout << "\n-- FOOD MARKET --\n" << endl;
        cout << "** Your Money : " << _money << " **\n" << endl;
        _zoo->showFoodStock();
        if (choice == 0) {cout << "> Buy seeds" << endl;}
        else {cout << "  Buy seeds : " << endl;}
        if (choice == 1) {cout << "> Buy meat" << endl;}
        else {cout << "  Buy meat : " << endl;}
        if (choice == 2) {cout << "> Exit" << endl;}
        else {cout << "  Exit" << endl;}

        int key = _getch();
        if (key == 72)
        {
            if (choice == 0) {continue;}
            else {choice -= 1;}
        }

        else if (key == 80)
        {
            if (choice == 3) {continue;}
            else {choice += 1;}
        }

        else if (key == 27)
        {
            cout << ">>> You have quit the game." << endl;
            exit(0);
        }

        else if (key == 13)
        {
            if (choice == 0 || choice == 1)
            {
                cout << ">> How much : ";
                quantity = askInput();
                // error handler
                while (quantity < 1)
                {
                    cout << "Wrong input. Try again :" << endl;
                    cin >> quantity;
                }
                // if seed
                if (choice == 0)
                {
                    int price = SEED_PRICE * quantity;
                    if (price > _money)
                    {
                        cout << "You don't have enough money." << endl;
                    }
                    else
                    {
                        _zoo->newSeedStock(quantity);
                        _money -= price;
                        cout << "You succesfully bought " << quantity << " kg of seed.\n" << endl;
                        this_thread::sleep_for(std::chrono::seconds(1));
                    }
                }
                // if meat
                else
                {
                    int price = MEAT_PRICE * quantity;
                    if (price > _money)
                    {
                        cout << "You don't have enough money." << endl;
                    }
                    else
                    {
                        _zoo->newMeatStock(quantity);
                        _money -= price;
                        cout << "You succesfully bought " << quantity << " kg of meat.\n" << endl;
                        this_thread::sleep_for(std::chrono::seconds(1));
                    }
                }
            }
            else
            {
                return;
            }
        }
    }
}

void Game::showAnimalToBuy(int action)
{
    if (action == 1) {cout << "> Tiger, 6 months : " << YOUNG_TIGER_BUY_PRICE << endl;}
    else {cout << "  Tiger, 6 months : " << YOUNG_TIGER_BUY_PRICE << endl;}
    if (action == 2) {cout << "> Tiger, 4 years old : " << ADULT_TIGER_BUY_PRICE << endl;}
    else {cout << "  Tiger, 4 years old : " << ADULT_TIGER_BUY_PRICE << endl;}
    if (action == 3) {cout << "> Tiger, 14 years old : " << OLD_TIGER_BUY_PRICE << endl;}
    else {cout << "  Tiger, 14 years old : " << OLD_TIGER_BUY_PRICE << endl;}
    if (action == 4) {cout << "> Eagle, 6 months : " << YOUNG_EAGLE_BUY_PRICE << endl;}
    else {cout << "  Eagle, 6 months : " << YOUNG_EAGLE_BUY_PRICE << endl;}
    if (action == 5) {cout << "> Eagle, 4 years : " << ADULT_EAGLE_BUY_PRICE << endl;}
    else {cout << "  Eagle, 4 years : " << ADULT_EAGLE_BUY_PRICE << endl;}
    if (action == 6) {cout << "> Eagle, 14 years old : " << OLD_EAGLE_BUY_PRICE << endl;}
    else {cout << "  Eagle, 14 years old : " << OLD_EAGLE_BUY_PRICE << endl;}
    if (action == 7) {cout << "> Hen, 6 months : " << YOUNG_HEN_BUY_PRICE << endl;}
    else {cout << "  Hen, 6 months : " << YOUNG_HEN_BUY_PRICE << endl;}
    if (action == 8) {cout << "> Rooster, 6 months : " << YOUNG_ROOSTER_BUY_PRICE << endl;}
    else {cout << "  Rooster, 6 months : " << YOUNG_ROOSTER_BUY_PRICE << endl;}
    if (action == 9) {cout << "> Exit animal market" << endl;}
    else {cout << "  Exit animal market" << endl;}
    cout << endl << endl;
}
// trade animals for money depending on player's choice
void Game::sellAnimalMenu()
{
    int choice = 1;
    while (true)
    {
        cout << typeid(Tiger *).name() << endl;
        // show prices
        vector<IAnimal *> chosen_type_list;
        vector<IAnimal *> chosen_age_list;
        int animal_to_sell = 0;
        int price = 0;
        string type = "";
        system("cls");
        showAnimalToSell(choice);

        int key = _getch();
        if (key == 72)
        {
            if (choice == 1) {continue;}
            else {choice -= 1;}
        }

        else if (key == 80)
        {
            if (choice == 9) {continue;}
            else {choice += 1;}
        }

        else if (key == 27)
        {
            cout << ">>> You have quit the game." << endl;
            exit(0);
        }

        else if (key == 13)
        {
            switch (choice)
                {
                case 1:
                    chosen_age_list = _zoo->getAnimalListByAge(0, 47);
                    type = "Tiger";
                    price = YOUNG_TIGER_SELL_PRICE;
                    break;
                case 2:
                    chosen_age_list = _zoo->getAnimalListByAge(47, 167);
                    type = "Tiger";
                    price = ADULT_TIGER_SELL_PRICE;
                    break;
                case 3:
                    chosen_age_list = _zoo->getAnimalListByAge(168, 999);
                    type = "Tiger";
                    price = OLD_TIGER_SELL_PRICE;
                    break;
                case 4:
                    chosen_age_list = _zoo->getAnimalListByAge(0, 47);
                    type = "Eagle";
                    price = YOUNG_EAGLE_SELL_PRICE;
                    break;
                case 5:
                    chosen_age_list = _zoo->getAnimalListByAge(47, 168);
                    price = ADULT_EAGLE_SELL_PRICE;
                    type = "Eagle";
                    break;
                case 6:
                    chosen_age_list = _zoo->getAnimalListByAge(168, 999);
                    price = OLD_EAGLE_SELL_PRICE;
                    type = "Eagle";
                    break;
                case 7:
                    chosen_age_list = _zoo->getAnimalListByGender("female");
                    price = YOUNG_HEN_BUY_PRICE;
                    type = "Chicken";
                    break;
                case 8:
                    chosen_age_list = _zoo->getAnimalListByGender("male");
                    price = YOUNG_ROOSTER_SELL_PRICE;
                    type = "Chicken";
                    break;
                case 9:
                    cout << "Exited animal market." << endl
                        << endl;
                    return;
                default:
                    cout << "Wrong input, try again." << endl
                        << endl;
                    continue;
                }
                // get animal from said type
                for (auto animal : chosen_age_list)
                {
                    if (animal->getType() == type)
                    {
                        chosen_type_list.push_back(animal); 
                    }
                }

                // if list is empty, continue
                if (chosen_type_list.size() == 0)
                {
                    cout << "You don't have this type of animal in your zoo." << endl << endl;
                    this_thread::sleep_for(std::chrono::seconds(1));
                    continue;
                }

                int choice2 = 0;
                int alpha = 0;
                while (true)
                {

                    int maxIndex = 10;
                    if (chosen_type_list.size() - alpha * 10 < 10)
                    {
                        maxIndex = chosen_type_list.size() - alpha * 10;
                    }
                    // show selected animals + "close" option
                    system("cls");
                    cout << "Who do you wanna sell ?" << endl << endl;
                    if (alpha != 0)
                    {
                        if (choice2 == -1) {cout << "> See Less" << endl;}
                        else {cout << "  See Less" << endl;}
                    }
                    for (int i = 0; i < maxIndex; i++)
                    {
                        if (i == choice2) {cout << "> ";}
                        else {cout << "  ";}
                        cout << chosen_type_list[i + alpha * 10]->getName() << ", " << chosen_type_list[i]->getGender() << ", " << chosen_type_list[i]->getAge() << endl;
                    }
                    if (alpha * 10 + maxIndex < chosen_type_list.size())
                    {
                        if (choice2 == maxIndex) {cout << "> See More" << endl;}
                        else {cout << "  See More" << endl;}
                    }
                    if (alpha * 10 + maxIndex >= chosen_type_list.size() && choice2 == maxIndex){cout << "> Return" << endl;}
                    else if (choice2 == maxIndex + 1) {cout << "> Return" << endl;}
                    else {cout << "  Return" << endl;}
                    // choose and sell the animal

                    int key = _getch();
                    if (key == 72)
                    {
                        if (alpha != 0 && choice2 == -1) {continue;}
                        if (choice2 == 0 && alpha == 0) {continue;}
                        else {choice2 -= 1;}
                    }

                    else if (key == 80)
                    {
                        if (alpha * 10 + maxIndex >= chosen_type_list.size() && choice2 == maxIndex) {continue;}
                        if (choice2 == maxIndex + 1) {continue;}
                        else {choice2 += 1;}
                    }

                    else if (key == 27)
                    {
                        cout << ">>> You have quit the game." << endl;
                        exit(0);
                    }

                    else if (key == 13)
                    {
                        if (alpha * 10 + maxIndex >= chosen_type_list.size() && choice2 == maxIndex || choice2 == maxIndex + 1)
                        {
                            break;
                        }
                        if (choice2 == maxIndex)
                        {
                            alpha += 1;
                            choice2 = 0;
                            continue;
                        }
                        if (choice2 == -1)
                        {
                            alpha -= 1;
                            choice2 = 9;
                            continue;
                        }
                            cout << "You sold " << chosen_type_list[choice2 + alpha * 10]->getName() << " to the meat market for " << price << "$ (you monster ! How could you !)" << endl;
                            _zoo->killAnimal(chosen_type_list[choice2 + alpha * 10]);
                            _money += price;
                            this_thread::sleep_for(std::chrono::seconds(3));
                            break;
                    }   
                }
            }
        }
}

// show sell price
void Game::showAnimalToSell(int action)
{
    cout << endl << "----- MEAT MARKET -----" << endl << endl;
    cout << "** Your Money : " << _money << " **\n" << endl;
    cout << "Those are the animals you can sell : " << endl;
    cout << "TIGERS" << endl;
    if (action == 1) {cout << "> Young tigers : " << YOUNG_TIGER_SELL_PRICE << endl;}
    else {cout << "  Young tigers : " << YOUNG_TIGER_SELL_PRICE << endl;}
    if (action == 2) {cout << "> Adult tigers : " << ADULT_TIGER_SELL_PRICE << endl;}
    else {cout << "  Adult tigers : " << ADULT_TIGER_SELL_PRICE << endl;}
    if (action == 3) {cout << "> Old tigers : " << OLD_TIGER_SELL_PRICE << endl;}
    else {cout << "  Old tigers : " << OLD_TIGER_SELL_PRICE << endl;}
    cout << "EAGLES" << endl;
    if (action == 4) {cout << "> Young eagles : " << YOUNG_EAGLE_SELL_PRICE << endl;}
    else {cout << "  Young eagles : " << YOUNG_EAGLE_SELL_PRICE << endl;}
    if (action == 5) {cout << "> Adult eagles : " << ADULT_EAGLE_SELL_PRICE << endl;}
    else {cout << "  Adult eagles : " << ADULT_EAGLE_SELL_PRICE << endl;}
    if (action == 6) {cout << "> Old eagles : " << OLD_EAGLE_SELL_PRICE << endl;}
    else {cout << "  Old eagles : " << OLD_EAGLE_SELL_PRICE << endl;}
    cout << "CHICKENS" << endl;
    if (action == 7) {cout << "> Hens : " << YOUNG_HEN_SELL_PRICE << endl;}
    else {cout << "  Hens : " << YOUNG_HEN_SELL_PRICE << endl;}
    if (action == 8) {cout << "> Roosters : " << YOUNG_ROOSTER_SELL_PRICE << endl;}
    else {cout << "  Roosters : " << YOUNG_ROOSTER_SELL_PRICE << endl;}
    cout << endl;
    if (action == 9) {cout << "> Exit animal market" << endl;}
    else {cout << "  Exit animal market" << endl;}
}

// sell empty cages depending on player choice. Give money
void Game::sellCage()
{
    int choice = 1;
    while (true)
    {
        system("cls");
        cout << "-- CAGE MARKET --" << endl;
        cout << "** Your Money : " << _money << " **\n" << endl;
        cout << "Cage price : (you can only sell empty cage)" << endl;
        if (choice == 1) {cout << "> Tiger cage price : " << TIGER_CAGE_SELL_PRICE << endl;}
        else {cout << "  Tiger cage price : " << TIGER_CAGE_SELL_PRICE << endl;}
        if (choice == 2) {cout << "> Eagle cage price : " << EAGLE_CAGE_SELL_PRICE << endl;}
        else {cout << "  Eagle cage price : " << EAGLE_CAGE_SELL_PRICE << endl;}
        if (choice == 3) {cout << "> Chicken cage price : " << CHICKEN_CAGE_SELL_PRICE << endl;}
        else {cout << "  Chicken cage price : " << CHICKEN_CAGE_SELL_PRICE << endl;}
        if (choice == 4) {cout << "> Exit cage market" << endl << endl;}
        else {cout << "  Exit cage market" << endl << endl;}

        // ask type of cage
        int key = _getch();
        if (key == 72)
        {
            if (choice == 1) {continue;}
            else {choice -= 1;}
        }

        else if (key == 80)
        {
            if (choice == 4) {continue;}
            else {choice += 1;}
        }

        else if (key == 27)
        {
            cout << ">>> You have quit the game." << endl;
            exit(0);
        }

        else if (key == 13)
        {
            string type;
            int price;

            switch (choice)
            {
            case 1:
                type = "Tiger";
                price = TIGER_CAGE_SELL_PRICE;
                break;
            case 2:
                type = "Eagle";
                price = EAGLE_CAGE_SELL_PRICE;
                break;
            case 3:
                type = "Chicken";
                price = CHICKEN_CAGE_SELL_PRICE;
                break;
            case 4:
                cout << "Exited cage market." << endl << endl;
                return;
            default :
                cout << "Wrong input. Try again." << endl << endl;
                continue;
            }

            // get sellable cages
            vector<Cage *> cage_list = _zoo->getCageList(type, "empty");
            if (cage_list.size() == 0)
            {
                cout << "You don't have empty " << type << " cages." << endl;
                this_thread::sleep_for(std::chrono::seconds(1));
                continue;
            }

            // ask how much
            cout << "You have " << cage_list.size() << " " << type << " cages." << endl
                << "How much do you wanna sell ?" << endl;
            int ncage_to_sell = askInput();

            // if not enough cages, abort
            if (ncage_to_sell > cage_list.size())
            {
                cout << "You don't have enough cages." << endl
                    << endl;
                this_thread::sleep_for(std::chrono::seconds(1));
                continue;
            }
            else
            {
                _money += price * ncage_to_sell;
                for (auto cage : cage_list)
                {
                    _zoo->deleteCage(cage);
                }
                cout << "You sold " << ncage_to_sell << " for " << price * ncage_to_sell << " $." << endl
                    << endl;
                this_thread::sleep_for(std::chrono::seconds(3));
            }
        }
    }
}