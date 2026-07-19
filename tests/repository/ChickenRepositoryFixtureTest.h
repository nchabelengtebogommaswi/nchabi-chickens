#include <catch2/catch_test_macros.hpp>

#include "../fixtures//DatabaseFixture.h"
#include "repositories/ChickenRepository.h"

class ChickenRepositoryFixtureTest : public DatabaseFixture
{
public:

    ChickenRepositoryFixtureTest()
        : repository(connection())
    {
    }

protected:

    ChickenRepository repository;
};