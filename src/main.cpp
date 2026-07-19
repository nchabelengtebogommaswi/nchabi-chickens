#include <iostream>
#include <filesystem>
#include "database/DatabaseConnection.h"
#include "repositories/ChickenRepository.h"

using namespace std;

int main()
{

    try
    {
        DatabaseConnection database("database/nchabi-chickens.db", "database/schema.sql");
        ChickenRepository chickenRepository(database);
        
        cout << "Database opened successfully.\n";
    }
    catch (const exception& ex)
    {
        cerr << ex.what() << '\n';
    }

    return 0;
}