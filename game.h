#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <string>
#include "zoo.h"
#include "config.h"

using namespace std;

class Game {
    string _playerName;
    int _money=BUDGET;
    int _currentMonth=STARTING_MONTH;
    int _currentYear=STARTING_YEAR;
    Zoo* _zoo;
public:
    void setScenario();
    void monthlyUpdate(string* story);
    int getMonth();
    int getYear();
    int getMoney();
    Zoo* getZoo();

    void setMoney(int change);

    void startGame();
    string parseDate();
    void newYear();
    void nextTurn();
    void menu(string);
    void buyAnimal();
    void buyFood();
    void buyCage();
    void showAnimalToBuy(int);
    void showAnimalToSell(int);
    void sellAnimalMenu();
    void sellCage();
};

#endif