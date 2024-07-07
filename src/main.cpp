#include "TaskManager.h"
#include "Database.h"
#include "ColorManager.hpp" // Include ColorManager.hpp for terminal colors
#include <iostream>
#include <limits>     // for std::numeric_limits
#include <fmt/core.h> // fmt library for formatted output
#include <future>     // for std::async, std::future

using fmt::print;
using std::async;
using std::future;
using std::launch;
using std::string;

// Function declarations
void displayMenu();
int getUserChoice();
void addTask(TaskManager &taskManager);
void listTasks(TaskManager &taskManager);
void markTaskDone(TaskManager &taskManager);
void deleteTask(TaskManager &taskManager);
void clearAllData(TaskManager &taskManager);

/**
 * @brief Main function for the Todo List CLI application.
 *
 * Initializes the database and task manager, displays a menu,
 * and handles user input to manage tasks.
 *
 * @return 0 on successful completion.
 */
int main()
{
    std::string filename = "tasks.db"; // Path of the database file
    Database database(filename);

    TaskManager taskManager(database);

    int choice;
    do
    {
        displayMenu();
        choice = getUserChoice();

        switch (choice)
        {
        case 1:
            addTask(taskManager);
            break;
        case 2:
            listTasks(taskManager);
            break;
        case 3:
            markTaskDone(taskManager);
            break;
        case 4:
            deleteTask(taskManager);
            break;
        case 5:
            fmt::print("{}Tasks saved. Exiting...\n{}", ColorManager::MAGENTA, ColorManager::RESET);
            break;
        case 6:
            clearAllData(taskManager);
            break;
        default:
            fmt::print("{}Invalid choice. Try again.\n{}", ColorManager::RED, ColorManager::RESET);
        }
    } while (choice != 5);

    return 0;
}

/**
 * @brief Displays the menu for the Todo List application.
 */
void displayMenu()
{
    // Display the menu with color using fmt for formatted output
    fmt::print("{}\nTodo List Menu\n{}\n", ColorManager::CYAN, ColorManager::RESET);
    fmt::print("1. {}Add Task{}\n", ColorManager::GREEN, ColorManager::RESET);
    fmt::print("2. {}List Tasks{}\n", ColorManager::YELLOW, ColorManager::RESET);
    fmt::print("3. {}Mark Task as Done{}\n", ColorManager::BLUE, ColorManager::RESET);
    fmt::print("4. {}Delete Task{}\n", ColorManager::RED, ColorManager::RESET);
    fmt::print("5. {}Save and Exit{}\n", ColorManager::MAGENTA, ColorManager::RESET);
    fmt::print("6. {}Clear All Data{}\n", ColorManager::BRIGHT_RED, ColorManager::RESET);
    fmt::print("Enter your choice: ");
}

/**
 * @brief Gets the user's menu choice with input validation.
 *
 * @return The user's choice as an integer.
 */
int getUserChoice()
{
    int choice;

    // Input validation
    while (!(std::cin >> choice) || choice < 1 || choice > 6)
    {
        std::cin.clear();                                                   // clear input buffer to restore cin to a usable state
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // ignore bad input
        fmt::print("{}Invalid choice. Please enter a number between 1 and 6.\n{}",
                   ColorManager::RED, ColorManager::RESET);
        fmt::print("Enter your choice: ");
    }
    std::cin.ignore();

    return choice;
}

/**
 * @brief Prompts the user to enter a task description and adds it to the task manager.
 *
 * @param taskManager Reference to the TaskManager object.
 */
void addTask(TaskManager &taskManager)
{
    std::string description;
    fmt::print("Enter task description: ");
    std::getline(std::cin, description);

    // Asynchronously add task
    auto addTaskFuture = async(launch::async, [&]()
                               { return taskManager.addTaskAsync(description); });

    // Wait for the task to complete before continuing
    addTaskFuture.get();
}

/**
 * @brief Asynchronously lists all tasks from the task manager.
 *
 * @param taskManager Reference to the TaskManager object.
 */
void listTasks(TaskManager &taskManager)
{
    // Asynchronously list tasks
    auto listTasksFuture = async(launch::async, [&]()
                                 { return taskManager.listTasksAsync(); });

    // Wait for the task to complete before continuing
    listTasksFuture.get();
}

/**
 * @brief Prompts the user to enter a task ID and marks it as done in the task manager.
 *
 * @param taskManager Reference to the TaskManager object.
 */
void markTaskDone(TaskManager &taskManager)
{
    int id;
    fmt::print("Enter task number to mark as done: ");
    std::cin >> id;

    // Asynchronously mark task as done
    auto markTaskDoneFuture = async(launch::async, [&]()
                                    { return taskManager.markTaskDoneAsync(id); });

    // Wait for the task to complete before continuing
    markTaskDoneFuture.get();
}

/**
 * @brief Prompts the user to enter a task ID and deletes it from the task manager.
 *
 * @param taskManager Reference to the TaskManager object.
 */
void deleteTask(TaskManager &taskManager)
{
    int id;
    fmt::print("Enter task number to delete: ");
    std::cin >> id;

    // Asynchronously delete task
    auto deleteTaskFuture = async(launch::async, [&]()
                                  { return taskManager.deleteTaskAsync(id); });

    // Wait for the task to complete before continuing
    deleteTaskFuture.get();
}

/**
 * @brief Asynchronously clears all tasks from the task manager.
 *
 * @param taskManager Reference to the TaskManager object.
 */
void clearAllData(TaskManager &taskManager)
{
    // Asynchronously clear all tasks
    auto clearAllDataFuture = async(launch::async, [&]()
                                    { return taskManager.clearAllDataAsync(); });

    // Wait for the task to complete before continuing
    clearAllDataFuture.get();

    fmt::print("{}All tasks cleared.\n{}", ColorManager::BRIGHT_RED, ColorManager::RESET);
}
