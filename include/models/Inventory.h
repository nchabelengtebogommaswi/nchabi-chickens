#pragma once

#include <string>
using namespace std;

struct Inventory
{
    int id{0};
    int productId{0};
    int quantity{0};
    string lastUpdated;
};