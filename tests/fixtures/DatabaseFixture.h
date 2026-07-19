#pragma once

#include <filesystem>
#include <memory>

#include "database/DatabaseConnection.h"

class DatabaseFixture
{
public:

    DatabaseFixture();

    virtual ~DatabaseFixture();

    DatabaseFixture(const DatabaseFixture&) = delete;
    DatabaseFixture& operator=(const DatabaseFixture&) = delete;

protected:

    DatabaseConnection& connection()
    {
        return *database;
    }

private:

    std::filesystem::path databasePath;

    std::unique_ptr<DatabaseConnection> database;
};