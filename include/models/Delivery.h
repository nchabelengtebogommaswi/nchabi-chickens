#pragma once

#include <string>
using namespace std;

struct Delivery
{
    int id{0};
    int salesOrderId{0};
    string driverName;
    string vehicle;
    string deliveryAddress;
    string deliveryDate;
    string status;
};