#include "TaskManager.h"
#include "ColorManager.hpp" // Include ColorManager.hpp for terminal colors
#include <iostream>
#include <iomanip> // for put_time
#include <ctime>
#include <future> // Add <future> header for std::async and std::launch

using std::async;
using std::future;
using std::launch;
using std::string;

/**
 * @brief Constructor to initialize TaskManager with a reference to the Database.
 *
 * @param db Reference to the Database object.
 */
TaskManager::TaskManager(Database &db) : database(db) {
    auto futureTasks = database.getTasksAsync();
    futureTasks.wait();
    tasks = futureTasks.get();
}

/**
 * @brief Asynchronous addition of a new task with the given description.
 *
 * Adds a new task to the database asynchronously using the Database object and updates the internal tasks list.
 *
 * @param description Description of the task to be added.
 * @return Future object for the add task operation.
 */
future<void> TaskManager::addTaskAsync(const string &description) {
    return async(launch::async, [this, description]()
                 {
        try {
            // Add task asynchronously
            auto future = database.addTaskAsync(description);
            future.wait(); // Wait for the asynchronous operation to complete
            // Update tasks asynchronously after addition
            auto futureTasks = database.getTasksAsync();
            futureTasks.wait();
            tasks = futureTasks.get();
        }
        catch (const std::exception &e) {
            std::cerr << "Error adding task asynchronously: " << e.what() << std::endl;
            throw; // Rethrow the exception to propagate it further
        } });
}

/**
 * @brief Asynchronous listing of all tasks with their IDs, descriptions, status (done or not done), and timestamps.
 *
 * Lists all tasks from the internal tasks list asynchronously. Uses ColorManager to display colored output.
 * Prints the task ID, description, status (done or not done), creation time, and if done, completion time.
 * Created time is displayed in BLUE, completed time (if applicable) is displayed in GREEN.
 *
 * @return Future object for the list tasks operation.
 */
future<void> TaskManager::listTasksAsync() const {
    return async(launch::async, [this]()
                 {
        try {
            auto futureTasks = database.getTasksAsync();
            futureTasks.wait();
            auto tasks = futureTasks.get();

            for (const auto &task : tasks) {
                // Using BLUE for task ID and description
                std::cout << Color::BLUE() << task.getId() << ". " << task.getDescription() << Color::RESET();

                // Using GREEN for done tasks and YELLOW for not done tasks
                if (task.isDone()) {
                    std::cout << Color::GREEN() << " [Done]" << Color::RESET();
                }
                else {
                    std::cout << Color::YELLOW() << " [Not Done]" << Color::RESET();
                }

                // Display creation time
                std::time_t createdTime = task.getCreatedTime();
                std::tm created_tm = *std::localtime(&createdTime);
                std::cout << " (Created: " << Color::GREEN() << std::put_time(&created_tm, "%Y-%m-%d %H:%M:%S") << Color::RESET();

                // Display completion time if task is done
                if (task.isDone()) {
                    std::time_t completedTime = task.getCompletedTime();
                    std::tm completed_tm = *std::localtime(&completedTime);
                    std::cout << Color::GREEN() << " (Completed: " << std::put_time(&completed_tm, "%Y-%m-%d %H:%M:%S") << ")" << Color::RESET();
                }
        std::cout << '\n';
            }
        }
        catch (const std::exception &e) {
            std::cerr << "Error listing tasks asynchronously: " << e.what() << std::endl;
            throw; // Rethrow the exception to propagate it further
        } });
}

/**
 * @brief Asynchronous marking of a task as done using its ID.
 *
 * Marks a task as done in the database asynchronously using the Database object and updates the internal tasks list.
 *
 * @param id ID of the task to be marked as done.
 * @return Future object for the mark task done operation.
 */
future<void> TaskManager::markTaskDoneAsync(int id) {
    return async(launch::async, [this, id]()
                 {
        try {
            // Mark task as done asynchronously
            auto future = database.markTaskDoneAsync(id);
            future.wait(); // Wait for the asynchronous operation to complete
            // Update tasks asynchronously after marking as done
            auto futureTasks = database.getTasksAsync();
            futureTasks.wait();
            tasks = futureTasks.get();
        }
        catch (const std::exception &e) {
            std::cerr << "Error marking task as done asynchronously: " << e.what() << std::endl;
            throw; // Rethrow the exception to propagate it further
        } });
}

/**
 * @brief Asynchronous deletion of a task using its ID.
 *
 * Deletes a task from the database asynchronously using the Database object and updates the internal tasks list.
 *
 * @param id ID of the task to be deleted.
 * @return Future object for the delete task operation.
 */
future<void> TaskManager::deleteTaskAsync(int id) {
    return async(launch::async, [this, id]()
                 {
        try {
            // Delete task asynchronously
            auto future = database.deleteTaskAsync(id);
            future.wait(); // Wait for the asynchronous operation to complete
            // Update tasks asynchronously after deletion
            auto futureTasks = database.getTasksAsync();
            futureTasks.wait();
            tasks = futureTasks.get();
        }
        catch (const std::exception &e) {
            std::cerr << "Error deleting task asynchronously: " << e.what() << std::endl;
            throw; // Rethrow the exception to propagate it further
        } });
}

/**
 * @brief Asynchronous clearing of all tasks from the database and reset of the internal tasks list.
 *
 * Deletes all tasks from the database using the Database object asynchronously and clears the internal tasks list.
 *
 * @return Future object for the clear all data operation.
 */
future<void> TaskManager::clearAllDataAsync() {
    return async(launch::async, [this]()
                 {
        try {
            auto future = database.clearAllDataAsync();
            future.wait(); // Wait for the asynchronous operation to complete
            // Update tasks asynchronously after clearing all data
            auto futureTasks = database.getTasksAsync();
            futureTasks.wait();
            tasks = futureTasks.get();
        }
        catch (const std::exception &e) {
            std::cerr << "Error clearing all data asynchronously: " << e.what() << std::endl;
            throw; // Rethrow the exception to propagate it further
        } });
}