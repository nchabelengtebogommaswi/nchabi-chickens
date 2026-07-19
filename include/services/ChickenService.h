#pragma once

#include <optional>
#include <string>

#include "models/Chicken.h"
#include "repositories/ChickenRepository.h"

class ChickenService
{
public:

    explicit ChickenService(ChickenRepository& repository);

    std::optional<Chicken> findByTagNumber(const std::string& tagNumber);

private:

    ChickenRepository& repository;
};