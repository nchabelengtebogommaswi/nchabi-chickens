#pragma once

#include <string>
using namespace std;

struct SalesOrder
{
    int id{0};
    int customerId{0};
    string orderDate;
    string status;
    double total{0.0};
};