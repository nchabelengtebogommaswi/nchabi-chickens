#include "DatabaseFixture.h"
#include <filesystem>

namespace fs = std::filesystem;

DatabaseFixture::DatabaseFixture()
    : databasePath("tests/data/test.db")
{
    //
    // Remove the previous database.
    //
    if (fs::exists(databasePath))
    {
        fs::remove(databasePath);
    }

    //
    // Ensure the directory exists.
    //
    fs::create_directories(databasePath.parent_path());

    //
    // Create a fresh database and execute schema.sql.
    //
    database = std::make_unique<DatabaseConnection>(
        databasePath.string(),
        "../../../database/schema.sql"
    );
}

DatabaseFixture::~DatabaseFixture()
{
    //
    // Close SQLite before deleting the file.
    //
    database.reset();

    if (fs::exists(databasePath))
    {
        fs::remove(databasePath);
    }
}