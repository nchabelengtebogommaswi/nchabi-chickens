#include "database/Statement.h"

#include <sqlite3.h>

#include <stdexcept>

using namespace std;

Statement::Statement(
    sqlite3* database,
    const std::string& sql)
    : statement(nullptr)
{
    const int result =
        sqlite3_prepare_v2(
            database,
            sql.c_str(),
            -1,
            &statement,
            nullptr);

    if (result != SQLITE_OK)
    {
        throw runtime_error(sqlite3_errmsg(database));
    }
}

Statement::~Statement()
{
    if (statement != nullptr)
    {
        sqlite3_finalize(statement);
        statement = nullptr;
    }
}

sqlite3_stmt* Statement::get() const
{
    return statement;
}

//---------------------------------------------------------
// Bind values
//---------------------------------------------------------

void Statement::bindInt(
    int index,
    int value)
{
    const int result =
        sqlite3_bind_int(
            statement,
            index,
            value);

    if (result != SQLITE_OK)
    {
        throw runtime_error("Failed to bind integer.");
    }
}

void Statement::bindDouble(
    int index,
    double value)
{
    const int result =
        sqlite3_bind_double(
            statement,
            index,
            value);

    if (result != SQLITE_OK)
    {
        throw runtime_error("Failed to bind double.");
    }
}

void Statement::bindText(
    int index,
    const std::string& value)
{
    const int result =
        sqlite3_bind_text(
            statement,
            index,
            value.c_str(),
            -1,
            SQLITE_TRANSIENT);

    if (result != SQLITE_OK)
    {
        throw runtime_error("Failed to bind text.");
    }
}

void Statement::bindNull(
    int index)
{
    const int result =
        sqlite3_bind_null(
            statement,
            index);

    if (result != SQLITE_OK)
    {
        throw runtime_error("Failed to bind null.");
    }
}

//---------------------------------------------------------
// Execute
//---------------------------------------------------------

void Statement::execute()
{
    const int result =
        sqlite3_step(statement);

    if (result != SQLITE_DONE)
    {
        throw runtime_error("SQL execution failed.");
    }
}

bool Statement::step()
{
    const int result =
        sqlite3_step(statement);

    if (result == SQLITE_ROW)
    {
        return true;
    }

    if (result == SQLITE_DONE)
    {
        return false;
    }

    throw runtime_error("Failed to step through result set.");
}

//---------------------------------------------------------
// Reading columns
//---------------------------------------------------------

int Statement::columnInt(
    int column) const
{
    return sqlite3_column_int(
        statement,
        column);
}

double Statement::columnDouble(
    int column) const
{
    return sqlite3_column_double(
        statement,
        column);
}

std::string Statement::columnText(
    int column) const
{
    const unsigned char* value =
        sqlite3_column_text(
            statement,
            column);

    if (value == nullptr)
    {
        return "";
    }

    return reinterpret_cast<const char*>(value);
}

//---------------------------------------------------------
// Reuse
//---------------------------------------------------------

void Statement::reset()
{
    sqlite3_reset(statement);
}

void Statement::clearBindings()
{
    sqlite3_clear_bindings(statement);
}