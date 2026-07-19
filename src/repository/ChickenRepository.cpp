#include <sqlite3.h>
#include "database/Statement.h"
#include "repositories/ChickenRepository.h"

using namespace std;

ChickenRepository::ChickenRepository(DatabaseConnection& databaseConnection)
    : databaseConnection(databaseConnection)
{
}


int ChickenRepository::insert(const Chicken& chicken)
{
    constexpr const char* insertSql = R"(
        INSERT INTO Chicken
        (
            TagNumber, Breed, Gender, HatchDate, PurchaseDate, WeightKg, Status, Pen, Notes, CreatedAt, UpdatedAt
        )
        VALUES
        (
            ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?
        );
    )";

    Statement insertStatement(databaseConnection.getHandle(), insertSql);

    insertStatement.bindText(1, chicken.tagNumber);
    insertStatement.bindText(2, chicken.breed);
    insertStatement.bindText(3, chicken.gender);
    insertStatement.bindText(4, chicken.hatchDate);
    insertStatement.bindText(5, chicken.purchaseDate);
    insertStatement.bindDouble(6, chicken.weightKg);
    insertStatement.bindText(7, chicken.status);
    insertStatement.bindText(8, chicken.pen);
    insertStatement.bindText(9, chicken.notes);
    insertStatement.bindText(10, chicken.createdAt);
    insertStatement.bindText(11, chicken.updatedAt);

    int result = sqlite3_step(insertStatement.get());

    if (result != SQLITE_DONE)
    {
        throw std::runtime_error(sqlite3_errmsg(databaseConnection.getHandle()));
    }

    return static_cast<int>(sqlite3_last_insert_rowid(databaseConnection.getHandle()));
}

bool ChickenRepository::update(const Chicken& chicken)
{
    throw runtime_error("ChickenRepository::update() not implemented.");
}

bool ChickenRepository::remove(int id)
{
    throw runtime_error("ChickenRepository::remove() not implemented.");
}

optional<Chicken> ChickenRepository::findById(int id)
{
    throw runtime_error("ChickenRepository::findById() not implemented.");
}

optional<Chicken> ChickenRepository::findByTagNumber(
    const string& tagNumber)
{
    constexpr const char* sql = R"(
        SELECT
            Id,
            TagNumber,
            Breed,
            Gender,
            HatchDate,
            PurchaseDate,
            WeightKg,
            Status,
            Pen,
            Notes,
            CreatedAt,
            UpdatedAt
        FROM Chicken
        WHERE TagNumber = ?;
    )";

    Statement statement(
        databaseConnection.getHandle(),
        sql);

    statement.bindText(1, tagNumber);

    if (!statement.step())
    {
        return nullopt;
    }

    Chicken chicken;

    chicken.id = statement.columnInt(0);
    chicken.tagNumber = statement.columnText(1);
    chicken.breed = statement.columnText(2);
    chicken.gender = statement.columnText(3);
    chicken.hatchDate = statement.columnText(4);
    chicken.purchaseDate = statement.columnText(5);
    chicken.weightKg = statement.columnDouble(6);
    chicken.status = statement.columnText(7);
    chicken.pen = statement.columnText(8);
    chicken.notes = statement.columnText(9);
    chicken.createdAt = statement.columnText(10);
    chicken.updatedAt = statement.columnText(11);

    return chicken;
}

vector<Chicken> ChickenRepository::findAll()
{
    throw runtime_error("ChickenRepository::findAll() not implemented.");
}