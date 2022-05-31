#include <iostream>
#include <string>
#include "game.h"
#include "zoo.h"
#include "config.h"

// run at the start, return true for new game, false to close the app
bool startGame()
{
    cout << "Welcome to ZOO SIMULATOR 3000 ! Do you want to start a game ? y/n" << endl;
    string start;
    cin >> start;
    if (start == "y")
    {
        return true;
    }
    else
    {
        return false;
    }
}

// date in full letters
string date(int *year, int *month)
{
    string date;
    switch (*month)
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

    date += ", YEAR " + to_string(*year);
    return date;
}

// happy new year !
void newYear(int *year, int *month)
{
    *month = 1;
    *year += 1;
    cout << "Hapy New Year !" << endl;
}

// player actions during turn. Loop untill skip turn
void playerActions(Zoo *zoo, int *money)
{
    int action = 0;
    while (action != 6)
    {
        cout << "Money :" << *money << endl;
        cout << "You can do the following actions :\n1) Buy new animals\n2) Sell animals\n3) Buy food\n4) Buy new cages\n5) Sell cages\n6) End turn\n\n"
             << endl;

        cin >> action;
        switch (action)
        {
        case 1:
            buyAnimal(zoo, money);
            break;
        // case 2:
        //     sellAnimal(zoo, money);
        //     break;
        case 3:
            zoo->buyFood(money);
            break;
        case 4:
            buyCage(zoo, money);
            break;
        // case 5 :
        //     sellCage(zoo, money);
        //     break;
        case 6:
            cout << "Turn ended." << endl;
            break;
        default:
            cout << "Wrong input, try again." << endl;
            break;
        }
    }
}

// buy an animal and add  it to the zoo
void buyAnimal(Zoo *zoo, int *money)
{
    cout << "\n-- ANIMAL MARKET --\n"
         << endl;
    int price = 0;
    int action = 0;
    string type = "";
    int age = 0;
    int gender = 0;

    while (true)
    {
        showAnimalToBuy();
        cout << "Action ?" << endl;
        cin >> action;

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
            cout << "Exited animal market."
                 << "\n"
                 << endl;
            return;
        default:
            cout << "Wrong input, try again."
                 << "\n"
                 << endl;
            continue;
        }

        if (*money < price)
        {
            cout << "You don't have enough money."
                 << "\n"
                 << endl;
            continue;
        }
        else
        {
            *money -= price;
        }

        // if gender is not defined, define it (1 for male, 2 for female):
        if (gender == 0)
        {
            cout << "Gender :"
                 << "\n"
                 << "1) Male"
                 << "\n"
                 << "2) Female" << endl;
            cin >> gender;
            while (gender != 1 && gender != 2)
            {
                cout << "Wrong input. Try again :" << endl;
                cin >> gender;
            }
        }

        // create the animal
        if (type == "Tiger")
        {
            Tiger *newAnimal = new Tiger(age, gender);
            zoo->addAnimal(newAnimal);
        }
        else if (type == "Eagle")
        {
            Eagle *newAnimal = new Eagle(age, gender);
            zoo->addAnimal(newAnimal);
        }
        else if (type == "Chicken")
        {
            Chicken *newAnimal = new Chicken(age, gender);
            zoo->addAnimal(newAnimal);
        }
        cout << endl;
    }
}

// buy cages depending on player's choice, then add it to the zoo
void buyCage(Zoo *zoo, int *money)
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
        if (type != "" && *money >= price)
        {
            Cage *newCage = new Cage(type);
            zoo->addCage(newCage);
            *money -= price;
        }
        else if (*money < price)
        {
            cout << "You don't have enough money." << endl;
        }
    }
}

void showAnimalToBuy()
{
    cout << "Available animals :" << endl
         << "1) Tiger, 6 months : " << YOUNG_TIGER_BUY_PRICE << endl
         << "2) Tiger, 4 years old : " << ADULT_TIGER_BUY_PRICE << endl
         << "3) Tiger, 14 years old : " << OLD_TIGER_BUY_PRICE << endl
         << "4) Eagle, 6 months : " << YOUNG_EAGLE_BUY_PRICE << endl
         << "5) Eagle, 4 years : " << ADULT_EAGLE_BUY_PRICE << endl
         << "6) Eagle, 14 years old : " << OLD_EAGLE_BUY_PRICE << endl
         << "7) Hen, 6 months : " << YOUNG_HEN_BUY_PRICE << endl
         << "8) Rooster, 6 months : " << YOUNG_ROOSTER_BUY_PRICE << endl
         << "9) Exit animal market"
         << "\n"
         << endl;
}