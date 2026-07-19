#pragma once

#include <optional>
#include <string>
#include <vector>
#include "models/Chicken.h"
#include "database/DatabaseConnection.h"

struct sqlite3_stmt;

using namespace std;

/**
 * Repository responsible for all database operations
 * on the Chicken table.
 */
class ChickenRepository
{
public:

    explicit ChickenRepository(DatabaseConnection& databaseConnection);

    ~ChickenRepository() = default;

    ChickenRepository(const ChickenRepository&) = delete;
    ChickenRepository& operator=(const ChickenRepository&) = delete;

    ChickenRepository(ChickenRepository&&) = delete;
    ChickenRepository& operator=(ChickenRepository&&) = delete;

public:

    int insert(const Chicken& chicken);
    bool update(const Chicken& chicken);
    bool remove(int id);
    optional<Chicken> findById(int id);
    optional<Chicken> findByTagNumber(const string& tagNumber);
    vector<Chicken> findAll();

private:

    DatabaseConnection& databaseConnection;
};