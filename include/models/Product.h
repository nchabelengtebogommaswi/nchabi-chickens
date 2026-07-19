#pragma once

#include <string>
using namespace std;

struct Product
{
    int id{0};
    string name;
    string unit;
    double sellingPrice{0.0};
    bool active{true};
};