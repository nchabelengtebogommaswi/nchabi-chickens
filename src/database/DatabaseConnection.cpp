#include "database/DatabaseConnection.h"
#include <sqlite3.h>
#include <stdexcept>
#include <fstream>
#include <sstream>

using namespace std;

DatabaseConnection::DatabaseConnection(
    const filesystem::path& p_databasePath,
    const filesystem::path& p_schemaPath)
    : databasePath(p_databasePath),
      schemaPath(p_schemaPath),
      database(nullptr)
{
    const bool databaseAlreadyExists = filesystem::exists(databasePath);
    open();

    if (!databaseAlreadyExists)
    {
        executeSchema();
    }
}

DatabaseConnection::~DatabaseConnection()
{
    close();
}

void DatabaseConnection::open()
{
    if (database != nullptr)
    {
        return;
    }

    filesystem::create_directories(databasePath.parent_path());
    int result = sqlite3_open( databasePath.c_str(), &database);

    if (result != SQLITE_OK)
    {
        string error = sqlite3_errmsg(database);
        sqlite3_close(database);
        database = nullptr;
        throw runtime_error("Failed to open database: " + error);
    }
}

void DatabaseConnection::close()
{
    int rc = sqlite3_close(database);

    if(rc != SQLITE_OK)
    {
        throw runtime_error(
            sqlite3_errmsg(database));
    }
    database = nullptr;
}

bool DatabaseConnection::isOpen() const
{
    return database != nullptr;
}

sqlite3* DatabaseConnection::getHandle() const
{
    return database;
}

void DatabaseConnection::executeSchema()
{
    ifstream file(schemaPath);

    if (!file.is_open())
    {
        throw runtime_error("Unable to open schema file: " + schemaPath.string());
    }

    stringstream buffer;
    buffer << file.rdbuf();
    execute(buffer.str());
}

void DatabaseConnection::execute(const string& p_sql)
{
    char* errorMessage = nullptr;
    int result = sqlite3_exec(database,p_sql.c_str(),nullptr,nullptr,&errorMessage);

    if (result != SQLITE_OK)
    {
        string error(errorMessage);

        sqlite3_free(errorMessage);
        throw runtime_error(error);
    }
}