#include "TaskManager.h"
#include "Database.h"
#include "ColorManager.hpp" // Include ColorManager.hpp for terminal colors
#include <iostream>
#include <limits> // for std::numeric_limits

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
        // Display the menu with color
        std::cout << ColorManager::CYAN << "\nTodo List Menu\n"
                  << ColorManager::RESET;
        std::cout << "1. " << ColorManager::GREEN << "Add Task\n"
                  << ColorManager::RESET;
        std::cout << "2. " << ColorManager::YELLOW << "List Tasks\n"
                  << ColorManager::RESET;
        std::cout << "3. " << ColorManager::BLUE << "Mark Task as Done\n"
                  << ColorManager::RESET;
        std::cout << "4. " << ColorManager::RED << "Delete Task\n"
                  << ColorManager::RESET;
        std::cout << "5. " << ColorManager::MAGENTA << "Save and Exit\n"
                  << ColorManager::RESET;
        std::cout << "6. " << ColorManager::BRIGHT_RED << "Clear All Data\n"
                  << ColorManager::RESET;
        std::cout << "Enter your choice: ";

        // Input validation
        while (!(std::cin >> choice) || choice < 1 || choice > 6)
        {
            std::cin.clear();                                                   // clear input buffer to restore cin to a usable state
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // ignore bad input
            std::cout << ColorManager::RED << "Invalid choice. Please enter a number between 1 and 6.\n"
                      << ColorManager::RESET;
            std::cout << "Enter your choice: ";
        }
        std::cin.ignore();

        switch (choice)
        {
        case 1:
        {
            std::string description;
            std::cout << "Enter task description: ";
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
            std::cout << "Enter task number to mark as done: ";
            std::cin >> id;
            taskManager.markTaskDone(id);
            break;
        }
        case 4:
        {
            int id;
            std::cout << "Enter task number to delete: ";
            std::cin >> id;
            taskManager.deleteTask(id);
            break;
        }
        case 5:
            std::cout << ColorManager::MAGENTA << "Tasks saved. Exiting...\n"
                      << ColorManager::RESET;
            return 0; // Exit the program
        case 6:
            taskManager.clearAllData();
            std::cout << ColorManager::BRIGHT_RED << "All tasks cleared.\n"
                      << ColorManager::RESET;
            break;
        default:
            // This case is actually handled by input validation, but keeping for completeness
            std::cout << ColorManager::RED << "Invalid choice. Try again.\n"
                      << ColorManager::RESET;
        }
    } while (choice != 5);

    return 0;
}
