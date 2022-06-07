#include <iostream>
#include <string>
#include <random>
#include "functions.h"

using namespace std;

// return random int
int randInt(int min, int max)
{
    random_device rd;  // obtain a random number from hardware
    mt19937 gen(rd()); // seed the generator
    uniform_int_distribution<> distr(min, max);
    return distr(gen);
}

//ask for input, return int
int askInput()
{
    string input;
    cin >> input;
    return stringToInt(input);
}

// check if string can be converted, then convert & return
int stringToInt(string s)
{
    try
    {
        int n = stoi(s);
        return n;
    }
    catch (invalid_argument)
    {
        return -1;
    }
}