#include "services/ChickenService.h"

using namespace std;

ChickenService::ChickenService(ChickenRepository& repository): repository(repository)
{
}

optional<Chicken> ChickenService::findByTagNumber(const string& tagNumber)
{
    return repository.findByTagNumber(tagNumber);
}