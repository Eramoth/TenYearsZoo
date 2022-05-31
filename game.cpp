#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include <conio.h>
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

Zoo* Game::getZoo()
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

// happy new year !
void Game::newYear()
{
    _currentMonth = 1;
    _currentYear += 1;
    cout << "Hapy New Year !" << endl;
}

void Game::nextTurn()
{
    _currentMonth += 1;
    if (_currentMonth > 12)
    {
        newYear();
    }
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
            // case 2:
            //     sellAnimal(zoo, money);
            //     break;
            // case 3:
            //     buyFood();
            //     break;
            case 4:
                buyCage();
                break;
            // case 5 :
            //     sellCage(zoo, _money);
            //     break;
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

// buy an animal and add  it to the zoo
void Game::buyAnimal()
{
    int price = 0;
    int action = 1;
    string type = "";   
    int age = 0;
    int gender = 0;

    while (true)
    {
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
                 << "\n"
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
            while (1)
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
                     // create the animal
                    if (type == "Tiger")
                    {
                        Tiger *newAnimal = new Tiger(age, gender+1);
                        _zoo->addAnimal(newAnimal);
                    }
                    else if (type == "Eagle")
                    {
                        Eagle *newAnimal = new Eagle(age, gender+1);
                        _zoo->addAnimal(newAnimal);
                    }
                    else if (type == "Chicken")
                    {
                        Chicken *newAnimal = new Chicken(age, gender+1);
                        _zoo->addAnimal(newAnimal);
                    }
                    cout << endl;
                    this_thread::sleep_for(std::chrono::seconds(3));
                    break;
                }
                }
            }
        }
}

// buy cages depending on player's choice, then add it to the zoo
void Game::buyCage()
{
    // show available items
    int action = 0;
    string type = "Eagle";
    cout << "\n-- CAGE MARKET --\n"
         << endl;
    cout << "Cages available :\n"
         << endl;
    cout << "1) Tiger cage : " << TIGER_CAGE_BUY_PRICE << endl;
    cout << "2) Eagle cage : " << EAGLE_CAGE_BUY_PRICE << endl;
    cout << "3) Chicken cage : " << CHICKEN_CAGE_BUY_PRICE << endl;
    cout << "4) Exit cage market"
         << endl;

    // player buy as much as he want/can
    while (true)
    {
        cout << endl;
        string type = "";
        int price = 0;
        cout << "Action : " << endl;
        cin >> action;

        switch (action)
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

        // add cages if possible
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