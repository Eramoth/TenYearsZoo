#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <string>
#include "zoo.h"

using namespace std;

bool startGame();
string date(int *year, int *month);
void newYear(int *year, int *month);
void playerActions(Zoo *zoo , int *money);
void buyAnimal(Zoo *zoo, int *money);
void buyCage(Zoo *zoo, int *money);
void showAnimalToBuy();
#endif