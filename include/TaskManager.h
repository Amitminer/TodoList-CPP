#ifndef TASKMANAGER_H
#define TASKMANAGER_H

#include <vector>
#include <string>
#include "Task.h"
#include "Database.h"
#include <future> // For std::future

using std::future;
using std::vector;
using std::string;
// TaskManager class manages a collection of tasks and interacts with the database.
class TaskManager
{
public:
    // Constructor to initialize TaskManager with a reference to the Database.
    TaskManager(Database &db);

    // Asynchronous addition of a new task with the given description.
    future<void> addTaskAsync(const string &description);

    // Asynchronous listing of all tasks.
    future<void> listTasksAsync() const;

    // Asynchronous marking of a task as done by its ID.
    future<void> markTaskDoneAsync(int id);

    // Asynchronous deletion of a task by its ID.
    future<void> deleteTaskAsync(int id);

    // Asynchronous clearing of all tasks data from the database.
    future<void> clearAllDataAsync();

private:
    Database &database; // Reference to the Database
    vector<Task> tasks; // Vector to store tasks
};

#endif // TASKMANAGER_H
