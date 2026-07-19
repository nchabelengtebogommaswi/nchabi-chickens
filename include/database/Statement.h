#pragma once

#include <string>

struct sqlite3;
struct sqlite3_stmt;

class Statement
{
public:

    Statement(
        sqlite3* database,
        const std::string& sql);

    ~Statement();

    Statement(const Statement&) = delete;
    Statement& operator=(const Statement&) = delete;

    //------------------------------------------
    // Bind values
    //------------------------------------------

    void bindInt(int index, int value);
    void bindDouble(int index, double value);
    void bindText(int index, const std::string& value);
    void bindNull(int index);

    //------------------------------------------
    // Execute
    //------------------------------------------

    bool step();
    void execute();

    //------------------------------------------
    // Reading columns
    //------------------------------------------

    int columnInt(int column) const;
    double columnDouble(int column) const;
    std::string columnText(int column) const;

    //------------------------------------------
    // Reuse
    //------------------------------------------

    void reset();
    void clearBindings();
    sqlite3_stmt* get() const;

private:

    sqlite3_stmt* statement;
};