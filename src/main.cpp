#include "TaskManager.h"
#include "Database.h"
#include <iostream>

int main()
{
    // Initialize the database and task Manager.
    Database database("tasks.db");
    TaskManager taskManager(database);

    int choice;
    do
    {
        // Display the menu.
        std::cout << "\nTodo List Menu\n";
        std::cout << "1. Add Task\n";
        std::cout << "2. List Tasks\n";
        std::cout << "3. Mark Task as Done\n";
        std::cout << "4. Delete Task\n";
        std::cout << "5. Save and Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;
        std::cin.ignore();

        switch (choice)
        {
        case 1:
        {
            // Add a new task.
            std::string description;
            std::cout << "Enter task description: ";
            std::getline(std::cin, description);
            taskManager.addTask(description);
            break;
        }
        case 2:
            // List all tasks.
            taskManager.listTasks();
            break;
        case 3:
        {
            // Mark a task as done.
            int id;
            std::cout << "Enter task number to mark as done: ";
            std::cin >> id;
            taskManager.markTaskDone(id);
            break;
        }
        case 4:
        {
            // Delete a task.
            int id;
            std::cout << "Enter task number to delete: ";
            std::cin >> id;
            taskManager.deleteTask(id);
            break;
        }
        case 5:
            // Save tasks to the database and exit.
            std::cout << "Tasks saved. Exiting...\n";
            break;
        default:
            // Invalid choice.
            std::cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 5);

    return 0;
}
