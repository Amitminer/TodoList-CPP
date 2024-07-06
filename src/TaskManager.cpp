#include "TaskManager.h"
#include "ColorManager.hpp" // Include ColorManager.hpp for terminal colors
#include <iostream>
#include <iomanip> // for put_time
#include <ctime>

/**
 * @brief Constructor to initialize TaskManager with a reference to the Database.
 *
 * @param db Reference to the Database object.
 */
TaskManager::TaskManager(Database &db) : database(db)
{
    tasks = database.getTasks();
}

/**
 * @brief Add a new task with the given description.
 *
 * Adds a new task to the database using the Database object and updates the internal tasks list.
 *
 * @param description Description of the task to be added.
 */
void TaskManager::addTask(const std::string &description)
{
    database.addTask(description);
    tasks = database.getTasks();
}

/**
 * @brief List all tasks with their IDs, descriptions, status (done or not done), and timestamps.
 *
 * Lists all tasks from the internal tasks list. Uses ColorManager to display colored output.
 * Prints the task ID, description, status (done or not done), creation time, and if done, completion time.
 * Created time is displayed in BLUE, completed time (if applicable) is displayed in GREEN.
 */
void TaskManager::listTasks() const
{
    for (const auto &task : tasks)
    {
        // Using BLUE for task ID and description
        std::cout << ColorManager::BLUE << task.getId() << ". " << task.getDescription() << ColorManager::RESET;

        // Using GREEN for done tasks and YELLOW for not done tasks
        if (task.isDone())
        {
            std::cout << ColorManager::GREEN << " [Done]" << ColorManager::RESET;
        }
        else
        {
            std::cout << ColorManager::YELLOW << " [Not Done]" << ColorManager::RESET;
        }

        // Display creation time
        std::time_t createdTime = task.getCreatedTime();
        std::tm created_tm = *std::localtime(&createdTime);
        std::cout << " (Created: " << ColorManager::GREEN << std::put_time(&created_tm, "%Y-%m-%d %H:%M:%S") << ColorManager::RESET;

        // Display completion time if task is done
        if (task.isDone())
        {
            std::time_t completedTime = task.getCompletedTime();
            std::tm completed_tm = *std::localtime(&completedTime);
            std::cout << ColorManager::GREEN << " (Completed: " << std::put_time(&completed_tm, "%Y-%m-%d %H:%M:%S") << ")" << ColorManager::RESET;
        }
        std::cout << '\n';
    }
}

/**
 * @brief Mark a task as done using its ID.
 *
 * Marks a task as done in the database using the Database object and updates the internal tasks list.
 *
 * @param id ID of the task to be marked as done.
 */
void TaskManager::markTaskDone(int id)
{
    if (id < 1 || id > tasks.size())
    {
        std::cerr << "Invalid task ID." << std::endl;
        return;
    }
    database.markTaskDone(id);
    tasks = database.getTasks();
}

/**
 * @brief Delete a task using its ID.
 *
 * Deletes a task from the database using the Database object and updates the internal tasks list.
 *
 * @param id ID of the task to be deleted.
 */
void TaskManager::deleteTask(int id)
{
    database.deleteTask(id);
    tasks = database.getTasks();
}

/**
 * @brief Clear all tasks from the database and reset the internal tasks list.
 *
 * Deletes all tasks from the database using the Database object and clears the internal tasks list.
 */
void TaskManager::clearAllData()
{
    for (const auto &task : tasks)
    {
        database.deleteTask(task.getId());
    }
    tasks.clear();
}
