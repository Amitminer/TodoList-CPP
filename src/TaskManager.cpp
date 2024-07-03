#include "TaskManager.h"
#include <iostream>

// Constructor: Initialize TaskManager and load tasks from the database.
TaskManager::TaskManager(Database &db) : database(db)
{
    tasks = database.getTasks();
}

// Add a new task to the manager and database.
void TaskManager::addTask(const std::string &description)
{
    database.addTask(description);
    tasks = database.getTasks();
}

// List all tasks with their status.
void TaskManager::listTasks() const
{
    for (const auto &task : tasks)
    {
        std::cout << task.getId() << ". " << task.getDescription() << " [" << (task.isDone() ? "Done" : "Not Done") << "]\n";
    }
}

// Mark a task as done by its ID and update the tasks list.
void TaskManager::markTaskDone(int id)
{
    database.markTaskDone(id);
    tasks = database.getTasks();
}

// Delete a task by its ID and update the tasks list.
void TaskManager::deleteTask(int id)
{
    database.deleteTask(id);
    tasks = database.getTasks();
}
