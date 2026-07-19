#include <iostream>
#include <filesystem>
#include "database/DatabaseConnection.h"

using namespace std;

int main()
{

    try
    {
        DatabaseConnection database("database/nchabi-chickens.db", "database/schema.sql");

        cout << "Database opened successfully.\n";
    }
    catch (const exception& ex)
    {
        cerr << ex.what() << '\n';
    }

    return 0;
}