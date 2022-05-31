#include <iostream>
#include <string>
#include "game.h"
#include "zoo.h"
#include "config.h"

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
    cout << "Welcome to ZOO SIMULATOR 3000 !" << endl;
    _zoo = new Zoo();
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
void Game::menu()
{
    int action = 0;
    while (action != 6)
    {
        cout << "Money :" << _money << endl;
        cout << "You can do the following actions :" << endl;
        cout << "1) Buy new animals" << endl;
        cout << "2) Sell animals" << endl;
        cout << "3) Buy food" << endl;
        cout << "4) Buy new cages" << endl;
        cout << "5) Sell cages" << endl;
        cout << "6) End turn" << endl
             << endl
             << endl;

        cin >> action;
        switch (action)
        {
        case 1:
            buyAnimal();
            break;
        case 2:
            sellAnimalMenu();
            break;
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
            break;
        default:
            cout << "Wrong input, try again." << endl;
            break;
        }
    }
}

// buy an animal and add  it to the zoo
void Game::buyAnimal()
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

        if (_money < price)
        {
            cout << "You don't have enough money."
                 << "\n"
                 << endl;
            continue;
        }
        else
        {
            _money -= price;
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
            _zoo->addAnimal(newAnimal);
        }
        else if (type == "Eagle")
        {
            Eagle *newAnimal = new Eagle(age, gender);
            _zoo->addAnimal(newAnimal);
        }
        else if (type == "Chicken")
        {
            Chicken *newAnimal = new Chicken(age, gender);
            _zoo->addAnimal(newAnimal);
        }
        cout << endl;
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

void Game::showAnimalToBuy()
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

// trade animals for money depending on player's choice
void Game::sellAnimalMenu()
{
    while (true)
    {
        cout << typeid(Tiger*).name() << endl;
        // show prices
        vector<IAnimal *> chosen_type_list;
        showAnimalToSell();
        int action = 0;
        int animal_to_sell = 0;
        int price = 0;

        // ask wich type & age of animal
        cin >> action;
        switch (action)
        {
        case 1:
            chosen_type_list = _zoo->getAnimalListByAge("Tiger", 0, 47);
            price = YOUNG_TIGER_SELL_PRICE;
            break;
        case 2:
            chosen_type_list = _zoo->getAnimalListByAge("Tiger", 47, 167);
            price = ADULT_TIGER_SELL_PRICE;
            break;
        case 3:
            chosen_type_list = _zoo->getAnimalListByAge("Tiger", 168, 999);
            price = OLD_TIGER_SELL_PRICE;
            break;
        case 4:
            chosen_type_list = _zoo->getAnimalListByAge("Eagle", 0, 47);
            price = YOUNG_EAGLE_SELL_PRICE;
            break;
        case 5:
            chosen_type_list = _zoo->getAnimalListByAge("Eagle", 47, 168);
            price = ADULT_EAGLE_SELL_PRICE;
            break;
        case 6:
            chosen_type_list = _zoo->getAnimalListByAge("Eagle", 168, 999);
            price = OLD_EAGLE_SELL_PRICE;
            break;
        case 7:
            chosen_type_list = _zoo->getAnimalListByGender("Chicken", "female");
            price = YOUNG_HEN_BUY_PRICE;
            break;
        case 8:
            chosen_type_list = _zoo->getAnimalListByGender("Chicken", "male");
            price = YOUNG_ROOSTER_SELL_PRICE;
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

        // if list is empty, continue
        if (chosen_type_list.size()==0)
        {
            cout << "You don't have this type of animal in your zoo." << endl << endl;
            continue;
        }

        // show selected animals + "close" option
        cout << "Who do you wanna sell ?" << endl << endl;
        for (int i= 0; i<chosen_type_list.size(); i++)
        {
            cout << i+1 << ") " << chosen_type_list[i]->getName() << ", " << chosen_type_list[i]->getGender() << ", " << chosen_type_list[i]->getAge() << endl;
        }
        cout << chosen_type_list.size()+1 << ") Return to animal market" << endl << endl;

        // choose and sell the animal
        cin >> animal_to_sell;
        if (animal_to_sell == chosen_type_list.size()+1)
        {
            continue;
        }
        else
        {
            cout << "You sold " << chosen_type_list[animal_to_sell-1]->getName() << " to the meat market for " << price << "$ (you monster ! How could you !)" << endl;
            _zoo->killAnimal(chosen_type_list[animal_to_sell-1]);
            _money+=price;
        }
    }
}

void Game::showAnimalToSell()
{
    cout << endl
         << "----- MEAT MARKET -----" << endl
         << endl;
    cout << "Those are the animals you can sell : " << endl;
    cout << "TIGERS" << endl;
    cout << "1) Young tigers : 1500" << endl
         << "2) Adult tigers : 600000" << endl
         << "3) Old tigers : 10000" << endl
         << endl;
    cout << "EAGLES" << endl;
    cout << "4) Young eagles : 500" << endl
         << "5) Adult eagles : 2000" << endl
         << "6) Old eagles : 400" << endl
         << endl;
    cout << "CHICKENS" << endl;
    cout << "7) Hen : 10" << endl
         << "8) Rooster : 20" << endl
         << endl;
    cout << "9) Exit animal market" << endl
         << endl;
}
