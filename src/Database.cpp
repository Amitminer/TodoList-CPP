#include "Database.h"
#include <SQLiteCpp/SQLiteCpp.h>
#include <SQLiteCpp/VariadicBind.h>
#include <iostream>
#include <ctime> // For std::time

/**
 * @brief Constructor to initialize the database connection and create the 'tasks' table if it doesn't exist.
 *
 * @param dbFilename Filename of the SQLite database.
 */
Database::Database(const std::string &dbFilename)
{
    // Open the SQLite database and create 'tasks' table if it doesn't exist
    db = new SQLite::Database(dbFilename, SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE);
    db->exec("CREATE TABLE IF NOT EXISTS tasks (id INTEGER PRIMARY KEY, description TEXT, done INTEGER, createdTime INTEGER, completedTime INTEGER)");
}

/**
 * @brief Destructor to close the SQLite database connection.
 */
Database::~Database()
{
    delete db;
}

/**
 * @brief Add a new task with the given description to the 'tasks' table.
 *
 * @param description Description of the task to be added.
 */
void Database::addTask(const std::string &description)
{
    // Get current time as a timestamp
    time_t now = std::time(nullptr);

    // Insert new task into 'tasks' table with creation time
    SQLite::Statement query(*db, "INSERT INTO tasks (description, done, createdTime, completedTime) VALUES (?, 0, ?, 0)");
    query.bind(1, description);
    query.bind(2, static_cast<int>(now));
    query.exec();
}

/**
 * @brief Retrieve all tasks from the 'tasks' table.
 *
 * @return Vector of Task objects representing all tasks in the database.
 */
std::vector<Task> Database::getTasks() const
{
    std::vector<Task> tasks;

    // Select all tasks from 'tasks' table
    SQLite::Statement query(*db, "SELECT id, description, done, createdTime, completedTime FROM tasks");
    while (query.executeStep())
    {
        // Create Task object and add to vector
        tasks.emplace_back(
            query.getColumn(0).getInt(),
            query.getColumn(1).getText(),
            query.getColumn(2).getInt() == 1,
            static_cast<time_t>(query.getColumn(3).getInt64()),
            static_cast<time_t>(query.getColumn(4).getInt64()));
    }
    return tasks;
}

/**
 * @brief Mark a task as done in the 'tasks' table by updating its 'done' status and setting completion time.
 *
 * @param id ID of the task to be marked as done.
 */
void Database::markTaskDone(int id)
{
    // Get current time as a timestamp
    time_t now = std::time(nullptr);

    // Update task in 'tasks' table to mark as done and set completion time
    SQLite::Statement query(*db, "UPDATE tasks SET done = 1, completedTime = ? WHERE id = ?");
    query.bind(1, static_cast<int>(now));
    query.bind(2, id);
    query.exec();
}

/**
 * @brief Delete a task from the 'tasks' table by its ID.
 *
 * @param id ID of the task to be deleted.
 */
void Database::deleteTask(int id)
{
    // Delete task from 'tasks' table by ID
    SQLite::Statement query(*db, "DELETE FROM tasks WHERE id = ?");
    query.bind(1, id);
    query.exec();
}
