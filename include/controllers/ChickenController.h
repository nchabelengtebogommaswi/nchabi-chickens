#pragma once

#include <httplib.h>

#include "services/ChickenService.h"

class ChickenController
{
public:

    explicit ChickenController(
        ChickenService& service);

    void registerRoutes(
        httplib::Server& server);

private:

    ChickenService& service;
};