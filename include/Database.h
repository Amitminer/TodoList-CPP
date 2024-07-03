#ifndef DATABASE_H
#define DATABASE_H

#include <vector>
#include "Task.h"
#include <SQLiteCpp/SQLiteCpp.h>

// Database class handles saving and loading tasks to/from a SQLite database.
class Database
{
public:
    // Constructor to initialize the database connection.
    Database(const std::string &dbFilename);

    // Destructor to close the database connection.
    ~Database();

    // Add a task to the database.
    void addTask(const std::string &description);

    // Get all tasks from the database.
    std::vector<Task> getTasks() const;

    // Mark a task as done in the database.
    void markTaskDone(int id);

    // Delete a task from the database.
    void deleteTask(int id);

private:
    SQLite::Database *db; // Pointer to the SQLite database
};

#endif // DATABASE_H
