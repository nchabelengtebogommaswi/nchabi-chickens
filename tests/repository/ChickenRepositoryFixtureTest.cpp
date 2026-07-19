#include "ChickenRepositoryFixtureTest.h"

#include <filesystem>
#include <iostream>

namespace fs = std::filesystem;

TEST_CASE("Insert ten chickens", "[ChickenRepository]")
{
    //
    // Build absolute paths from the project root.
    //
    const fs::path projectRoot = PROJECT_SOURCE_DIR;

    const fs::path databasePath =
            projectRoot /
            "tests" /
            "data" /
            "test.db";

    const fs::path schemaPath =
            projectRoot /
            "database" /
            "schema.sql";

    //
    // Display paths (very useful while learning)
    //
    std::cout << "Project Root : " << projectRoot << '\n';
    std::cout << "Database     : " << databasePath << '\n';
    std::cout << "Schema       : " << schemaPath << '\n';

    //
    // Ensure the directory exists.
    //
    fs::create_directories(databasePath.parent_path());

    //
    // Delete any previous test database.
    //
    if (fs::exists(databasePath))
    {
        fs::remove(databasePath);
    }

    //
    // Verify schema.sql exists.
    //
    REQUIRE(fs::exists(schemaPath));

    //
    // Create a fresh database.
    //
    DatabaseConnection database(
        databasePath.string(),
        schemaPath.string());

    ChickenRepository repository(database);

    //
    // Insert 5 Layers
    //
    for (int i = 1; i <= 5; ++i)
    {
        Chicken chicken;

        chicken.tagNumber = "LAYER-" + std::to_string(i);
        chicken.breed = "Hy-Line Brown";
        chicken.gender = "Female";
        chicken.hatchDate = "2026-07-19";
        chicken.purchaseDate = "2026-07-19";
        chicken.weightKg = 1.4;
        chicken.status = "ACTIVE";
        chicken.pen = "LAYERS";
        chicken.notes = "";
        chicken.createdAt = "2026-07-19";
        chicken.updatedAt = "2026-07-19";

        REQUIRE(repository.insert(chicken) == i);
    }

    //
    // Insert 5 Broilers
    //
    for (int i = 6; i <= 10; ++i)
    {
        Chicken chicken;

        chicken.tagNumber = "BROILER-" + std::to_string(i - 5);
        chicken.breed = "Cobb 500";
        chicken.gender = "Male";
        chicken.hatchDate = "2026-07-19";
        chicken.purchaseDate = "2026-07-19";
        chicken.weightKg = 2.2;
        chicken.status = "ACTIVE";
        chicken.pen = "BROILERS";
        chicken.notes = "";
        chicken.createdAt = "2026-07-19";
        chicken.updatedAt = "2026-07-19";

        REQUIRE(repository.insert(chicken) == i);
    }
}