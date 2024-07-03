#ifndef TASKMANAGER_H
#define TASKMANAGER_H

#include <vector>
#include <string>
#include "Task.h"
#include "Database.h"

// TaskManager class manages a collection of tasks and interacts with the database.
class TaskManager
{
public:
    // Constructor to initialize TaskManager with a reference to the Database.
    TaskManager(Database &db);

    // Add a new task.
    void addTask(const std::string &description);

    // List all tasks.
    void listTasks() const;

    // Mark a task as done by its ID.
    void markTaskDone(int id);

    // Delete a task by its ID.
    void deleteTask(int id);

    // Clear all tasks data from the database.
    void clearAllData();

private:
    Database &database;      // Reference to the Database
    std::vector<Task> tasks; // Vector to store tasks
};

#endif // TASKMANAGER_H
