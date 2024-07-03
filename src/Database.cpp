#include "Database.h"
#include <SQLiteCpp/SQLiteCpp.h>
#include <SQLiteCpp/VariadicBind.h>
#include <iostream>

// Constructor: Initialize the database connection and create the tasks table if it doesn't exist.
Database::Database(const std::string &dbFilename)
{
    db = new SQLite::Database(dbFilename, SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE);
    db->exec("CREATE TABLE IF NOT EXISTS tasks (id INTEGER PRIMARY KEY, description TEXT, done INTEGER)");
}

// Destructor: Close the database connection.
Database::~Database()
{
    delete db;
}

// Add a task to the database.
void Database::addTask(const std::string &description)
{
    SQLite::Statement query(*db, "INSERT INTO tasks (description, done) VALUES (?, 0)");
    query.bind(1, description);
    query.exec();
}

// Retrieve all tasks from the database.
std::vector<Task> Database::getTasks() const
{
    std::vector<Task> tasks;
    SQLite::Statement query(*db, "SELECT id, description, done FROM tasks");
    while (query.executeStep())
    {
        tasks.emplace_back(query.getColumn(0).getInt(), query.getColumn(1).getText(), query.getColumn(2).getInt() == 1);
    }
    return tasks;
}

// Mark a task as done in the database.
void Database::markTaskDone(int id)
{
    SQLite::Statement query(*db, "UPDATE tasks SET done = 1 WHERE id = ?");
    query.bind(1, id);
    query.exec();
}

// Delete a task from the database.
void Database::deleteTask(int id)
{
    SQLite::Statement query(*db, "DELETE FROM tasks WHERE id = ?");
    query.bind(1, id);
    query.exec();
}
