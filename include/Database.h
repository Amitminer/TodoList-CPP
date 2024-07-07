#ifndef DATABASE_H
#define DATABASE_H

#include <vector>
#include "Task.h"
#include <future>
#include <SQLiteCpp/SQLiteCpp.h> // SQLiteCpp is a C++ library for accessing SQLite databases

using std::future;

/**
 * @class Database
 * @brief Manages SQLite database operations asynchronously.
 *
 * This class handles the initialization, finalization, and
 * various CRUD operations on the 'tasks' table in an SQLite
 * database, providing asynchronous methods for non-blocking
 * database access.
 */
class Database
{

public:
    /**
     * @brief Constructs a Database object and initializes the connection asynchronously.
     *
     * @param dbFilename Filename of the SQLite database.
     */
    explicit Database(const std::string &dbFilename);

    /**
     * @brief Destructs the Database object and finalizes the connection asynchronously.
     */
    ~Database();

    /**
     * @brief Asynchronous initialization of the database connection.
     *
     * @param dbFilename Filename of the SQLite database.
     * @return Future object for the initialization task.
     */
    future<void> initializeAsync(const std::string &dbFilename);

    /**
     * @brief Asynchronous destruction of the database connection.
     *
     * @return Future object for the finalization task.
     */
    future<void> finalizeAsync();

    /**
     * @brief Adds a task to the database asynchronously.
     *
     * @param description Description of the task to be added.
     * @return Future object for the add task operation.
     */
    future<void> addTaskAsync(const std::string &description);

    /**
     * @brief Retrieves all tasks from the database asynchronously.
     *
     * @return Future object containing a vector of Task objects.
     */
    future<std::vector<Task>> getTasksAsync() const;

    /**
     * @brief Marks a task as done in the database asynchronously.
     *
     * @param id ID of the task to be marked as done.
     * @return Future object for the mark task done operation.
     */
    future<void> markTaskDoneAsync(int id);

    /**
     * @brief Deletes a task from the database asynchronously.
     *
     * @param id ID of the task to be deleted.
     * @return Future object for the delete task operation.
     */
    future<void> deleteTaskAsync(int id);

    /**
     * @brief Clears all tasks from the database asynchronously.
     *
     * @return Future object for the clear all data operation.
     */
    future<void> clearAllDataAsync();

private:
    SQLite::Database *db; ///< Pointer to the SQLite database instance.
};

#endif // DATABASE_H
