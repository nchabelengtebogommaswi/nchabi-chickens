#pragma once

#include <string>
using namespace std;

struct Chicken
{
    int id{0};
    string tagNumber;
    string breed;
    string gender;
    string hatchDate;
    string purchaseDate;
    double weightKg{0.0};
    string status;
    string pen;
    string notes;
    string createdAt;
    string updatedAt;
};