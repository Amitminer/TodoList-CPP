#include "TaskManager.h"
#include "Database.h"
#include "ColorManager.hpp" // Include ColorManager.hpp for terminal colors
#include <iostream>
#include <limits>     // for std::numeric_limits
#include <fmt/core.h> // fmt library for formatted output

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
    Database database("tasks.db");
    TaskManager taskManager(database);

    int choice;
    do
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

        switch (choice)
        {
        case 1:
        {
            std::string description;
            fmt::print("Enter task description: ");
            std::getline(std::cin, description);
            taskManager.addTask(description);
            break;
        }
        case 2:
            taskManager.listTasks();
            break;
        case 3:
        {
            int id;
            fmt::print("Enter task number to mark as done: ");
            std::cin >> id;
            taskManager.markTaskDone(id);
            break;
        }
        case 4:
        {
            int id;
            fmt::print("Enter task number to delete: ");
            std::cin >> id;
            taskManager.deleteTask(id);
            break;
        }
        case 5:
            fmt::print("{}Tasks saved. Exiting...\n{}", ColorManager::MAGENTA, ColorManager::RESET);
            return 0; // Exit the program
        case 6:
            taskManager.clearAllData();
            fmt::print("{}All tasks cleared.\n{}", ColorManager::BRIGHT_RED, ColorManager::RESET);
            break;
        default:
            // This case is actually handled by input validation, but keeping for completeness
            fmt::print("{}Invalid choice. Try again.\n{}", ColorManager::RED, ColorManager::RESET);
        }
    } while (choice != 5);

    return 0;
}