#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <iostream>
#include <stdexcept>
using namespace std;
class DeadError : public exception
{
    public:
        const char *what()
    {
        return "You have died";
    }
};

class WinError : public exception
{
    public:
        const char *what()
    {
        return "You win!!!";
    }
};


class OverflowError : public exception
{
public:
    const char *what()
{
        return "Overflow Error Occured";
    }
};

class UnderflowError : public exception
{
public:
    const char *what()
    {
        return "Underflow Error Occured";
    }
};

class NotFound : public exception
{
public:
    const char *what()
    {
        return "Item Not Found";
    }
};

#endif