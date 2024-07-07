#include "Database.h"
#include <SQLiteCpp/SQLiteCpp.h>
#include <SQLiteCpp/VariadicBind.h>
#include <iostream>
#include <ctime>  // For std::time
#include <future> // For std::future

using std::async;
using std::future;
using std::launch;
using std::string;

/**
 * @brief Constructs a Database object and initializes the database asynchronously.
 *
 * @param dbFilename Filename of the SQLite database.
 */
Database::Database(const string &dbFilename) : db(nullptr) {
    // Constructor initializes the database asynchronously
    initializeAsync(dbFilename).get(); // Wait for initialization to complete
}

/**
 * @brief Destructor for cleaning up resources associated with the Database object.
 */
Database::~Database() {
    // Destructor finalizes the database asynchronously
    finalizeAsync().get(); // Ensure database is properly finalized
}

/**
 * @brief Asynchronous initialization of the database connection and creation of the 'tasks' table if it doesn't exist.
 *
 * @param dbFilename Filename of the SQLite database.
 * @return Future object for the initialization task.
 */
future<void> Database::initializeAsync(const string &dbFilename) {
    return async(launch::async, [this, dbFilename]()
                 {
        try {
            db = new SQLite::Database(dbFilename, SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE);
            db->exec("CREATE TABLE IF NOT EXISTS tasks (id INTEGER PRIMARY KEY, description TEXT, done INTEGER, createdTime INTEGER, completedTime INTEGER)");
        }
        catch (const SQLite::Exception &e) {
            std::cerr << "SQLite error (constructor): " << e.what() << std::endl;
            throw; // Rethrow the exception to propagate it further
        } });
}

/**
 * @brief Asynchronous destruction of the database connection.
 *
 * @return Future object for the finalization task.
 */
future<void> Database::finalizeAsync() {
    return async(launch::async, [this]()
                 {
        try {
            delete db;
        }
        catch (const SQLite::Exception &e) {
            std::cerr << "SQLite error (destructor): " << e.what() << std::endl;
            // Handle any specific actions or log the error
        } });
}

/**
 * @brief Asynchronous addition of a task to the 'tasks' table.
 *
 * @param description Description of the task to be added.
 * @return Future object for the add task operation.
 */
future<void> Database::addTaskAsync(const string &description) {
    return async(launch::async, [this, description]()
                 {
        try {
            time_t now = std::time(nullptr);
            SQLite::Statement query(*db, "INSERT INTO tasks (description, done, createdTime, completedTime) VALUES (?, 0, ?, 0)");
            query.bind(1, description);
            query.bind(2, static_cast<int>(now));
            query.exec();
        }
        catch (const SQLite::Exception &e) {
            std::cerr << "SQLite error (addTask): " << e.what() << std::endl;
            throw; // Rethrow the exception to propagate it further
        } });
}

/**
 * @brief Asynchronous retrieval of all tasks from the 'tasks' table.
 *
 * @return Future object for the get tasks operation.
 */
future<std::vector<Task>> Database::getTasksAsync() const {
    return async(launch::async, [this]() -> std::vector<Task>
                 {
        std::vector<Task> tasks;
        try {
            SQLite::Statement query(*db, "SELECT id, description, done, createdTime, completedTime FROM tasks");
            while (query.executeStep()) {
                tasks.emplace_back(
                    query.getColumn(0).getInt(),
                    query.getColumn(1).getText(),
                    query.getColumn(2).getInt() == 1,
                    static_cast<time_t>(query.getColumn(3).getInt64()),
                    static_cast<time_t>(query.getColumn(4).getInt64()));
            }
        }
        catch (const SQLite::Exception &e) {
            std::cerr << "SQLite error (getTasks): " << e.what() << std::endl;
            throw; // Rethrow the exception to propagate it further
        }
        return tasks; });
}

/**
 * @brief Asynchronous marking of a task as done in the 'tasks' table.
 *
 * @param id ID of the task to be marked as done.
 * @return Future object for the mark task done operation.
 */
future<void> Database::markTaskDoneAsync(int id) {
    return async(launch::async, [this, id]()
                 {
        try {
            time_t now = std::time(nullptr);
            SQLite::Statement query(*db, "UPDATE tasks SET done = 1, completedTime = ? WHERE id = ?");
            query.bind(1, static_cast<int>(now));
            query.bind(2, id);
            query.exec();
        }
        catch (const SQLite::Exception &e) {
            std::cerr << "SQLite error (markTaskDone): " << e.what() << std::endl;
            throw; // Rethrow the exception to propagate it further
        } });
}

/**
 * @brief Asynchronous deletion of a task from the 'tasks' table by ID.
 *
 * @param id ID of the task to be deleted.
 * @return Future object for the delete task operation.
 */
future<void> Database::deleteTaskAsync(int id) {
    return async(launch::async, [this, id]()
                 {
        try {
            SQLite::Statement query(*db, "DELETE FROM tasks WHERE id = ?");
            query.bind(1, id);
            query.exec();
        }
        catch (const SQLite::Exception &e) {
            std::cerr << "SQLite error (deleteTask): " << e.what() << std::endl;
            throw; // Rethrow the exception to propagate it further
        } });
}

/**
 * @brief Asynchronous clearing of all tasks from the 'tasks' table.
 *
 * @return Future object for the clear all data operation.
 */
future<void> Database::clearAllDataAsync() {
    return async(launch::async, [this]()
                 {
        try {
            SQLite::Transaction transaction(*db);
            db->exec("DELETE FROM tasks"); // Delete all rows from 'tasks' table
            transaction.commit(); // Commit the transaction
        }
        catch (const SQLite::Exception &e) {
            std::cerr << "SQLite error (clearAllData): " << e.what() << std::endl;
            throw; // Rethrow the exception to propagate it further
        } });
}
