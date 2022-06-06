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
    int getMonth();
    int getYear();
    Zoo* getZoo();

    void startGame();
    string parseDate();
    int askInput();
    void newYear();
    void nextTurn();
    void menu(string);
    void buyAnimal();
    void buyCage();
    void buyFood();
    void showAnimalToBuy(int);
    void showAnimalToBuy();
    void showAnimalToSell();
    void sellAnimalMenu();
    void sellCage();
    int stringToInt(string s);
};

#endif