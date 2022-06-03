#ifndef IANIMAL_H
#define IANIMAL_H
#include <string>
#include "zoo.h"

using namespace std;

class Zoo;

class IAnimal
{
protected:
    string _name;
    int _age;
    int _age_of_death;
    int _gender; // 1 for male, 2 for female
    // string _diet; // pointless to keep here because of #define ?
    // int _food_quantity; // pointless to keep here because of #define ?
    int _month_since_meal;
    bool _is_sick;
    // int _child_by_birth; // _child_by_litter, probably useless with #define
    int _gestation_month;
    bool _fresh_new; // true if animal has been created this month, can be replaced by an array of "new animals" reset every month

public:
    IAnimal(int age, int gender, int age_of_death);
    ~IAnimal();
    void kill(Zoo *zoo);
    string getName();
    string getGender();
    int getAge();
    void increaseAge(Zoo *zoo);
    void escape(); // will be virtual void
    virtual void showAnimal() = 0;
    virtual bool canReproduce() = 0;
    // virtual void giveBirth() = 0;
    // virtual bool isHungy() = 0;
    // virtual void feed() = 0; // will update _month_since_meal
};

// tiger
class Tiger:public IAnimal
{
private:
    string _partner;
public:
    Tiger(int age, int gender);
    ~Tiger();
    virtual void showAnimal();
    virtual bool canReproduce();
};

// eagle
class Eagle:public IAnimal
{
private:
    string _partner;
public:
    Eagle(int age, int gender);
    ~Eagle();
    virtual void showAnimal();
    virtual bool canReproduce();
};

// chicken
class Chicken:public IAnimal
{
private:
    string _partner;
public:
    Chicken(int age, int gender);
    ~Chicken();
    virtual void showAnimal();
    virtual bool canReproduce();
};

#endif