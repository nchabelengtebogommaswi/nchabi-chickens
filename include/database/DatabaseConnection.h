#pragma once

#include <string>
#include <filesystem>
struct sqlite3;

using namespace std;

/**
 * @brief Manages the lifetime of a SQLite database connection.
 *
 * Responsibilities:
 *  - Open the database
 *  - Close the database
 *  - Execute SQL statements
 *  - Execute schema files
 *  - Manage transactions
 *
 * This class follows the RAII principle.
 */
class DatabaseConnection
{
    public:

        /**
         * Constructor.
         *
         * @param databasePath Path to the SQLite database.
         */
        explicit DatabaseConnection(const filesystem::path& p_databasePath, const filesystem::path& p_schemaPath);

        /**
         * Destructor.
         */
        ~DatabaseConnection();

        DatabaseConnection(const DatabaseConnection&) = delete;
        DatabaseConnection& operator=(const DatabaseConnection&) = delete;

        DatabaseConnection(DatabaseConnection&&) = delete;
        DatabaseConnection& operator=(DatabaseConnection&&) = delete;

        //---------------------------------------------------------
        // Connection
        //---------------------------------------------------------

        void open();

        void close();

        bool isOpen() const;

        //---------------------------------------------------------
        // SQL Execution
        //---------------------------------------------------------

        void execute(const string& p_sql);

        void executeFile(const string& p_filename);

        //---------------------------------------------------------
        // Transactions
        //---------------------------------------------------------

        void beginTransaction();

        void commit();

        void rollback();

        //---------------------------------------------------------
        // Low-level access
        //---------------------------------------------------------

        sqlite3* getHandle() const;

    private:
        void executeSchema();

        filesystem::path databasePath;
        filesystem::path schemaPath;
        sqlite3* database;
};