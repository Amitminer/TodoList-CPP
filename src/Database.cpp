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
    try
    {
        // Open the SQLite database and create 'tasks' table if it doesn't exist
        db = new SQLite::Database(dbFilename, SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE);
        db->exec("CREATE TABLE IF NOT EXISTS tasks (id INTEGER PRIMARY KEY, description TEXT, done INTEGER, createdTime INTEGER, completedTime INTEGER)");
    }
    catch (const SQLite::Exception &e)
    {
        std::cerr << "SQLite error (constructor): " << e.what() << std::endl;
        // Handle any specific actions or rethrow if necessary
        throw; // Rethrow the exception to propagate it further
    }
}

/**
 * @brief Destructor to close the SQLite database connection.
 */
Database::~Database()
{
    try
    {
        delete db;
    }
    catch (const SQLite::Exception &e)
    {
        std::cerr << "SQLite error (destructor): " << e.what() << std::endl;
        // Handle any specific actions or log the error
    }
}

/**
 * @brief Add a new task with the given description to the 'tasks' table.
 *
 * @param description Description of the task to be added.
 */
void Database::addTask(const std::string &description)
{
    try
    {
        // Get current time as a timestamp
        time_t now = std::time(nullptr);

        // Insert new task into 'tasks' table with creation time
        SQLite::Statement query(*db, "INSERT INTO tasks (description, done, createdTime, completedTime) VALUES (?, 0, ?, 0)");
        query.bind(1, description);
        query.bind(2, static_cast<int>(now));
        query.exec();
    }
    catch (const SQLite::Exception &e)
    {
        std::cerr << "SQLite error (addTask): " << e.what() << std::endl;
        // Handle any specific actions or rethrow if necessary
        throw; // Rethrow the exception to propagate it further
    }
}

/**
 * @brief Retrieve all tasks from the 'tasks' table.
 *
 * @return Vector of Task objects representing all tasks in the database.
 */
std::vector<Task> Database::getTasks() const
{
    std::vector<Task> tasks;

    try
    {
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
    }
    catch (const SQLite::Exception &e)
    {
        std::cerr << "SQLite error (getTasks): " << e.what() << std::endl;
        // Handle any specific actions or rethrow if necessary
        throw; // Rethrow the exception to propagate it further
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
    try
    {
        // Get current time as a timestamp
        time_t now = std::time(nullptr);

        // Update task in 'tasks' table to mark as done and set completion time
        SQLite::Statement query(*db, "UPDATE tasks SET done = 1, completedTime = ? WHERE id = ?");
        query.bind(1, static_cast<int>(now));
        query.bind(2, id);
        query.exec();
    }
    catch (const SQLite::Exception &e)
    {
        std::cerr << "SQLite error (markTaskDone): " << e.what() << std::endl;
        // Handle any specific actions or rethrow if necessary
        throw; // Rethrow the exception to propagate it further
    }
}

/**
 * @brief Delete a task from the 'tasks' table by its ID.
 *
 * @param id ID of the task to be deleted.
 */
void Database::deleteTask(int id)
{
    try
    {
        // Delete task from 'tasks' table by ID
        SQLite::Statement query(*db, "DELETE FROM tasks WHERE id = ?");
        query.bind(1, id);
        query.exec();
    }
    catch (const SQLite::Exception &e)
    {
        std::cerr << "SQLite error (deleteTask): " << e.what() << std::endl;
        // Handle any specific actions or rethrow if necessary
        throw; // Rethrow the exception to propagate it further
    }
}
