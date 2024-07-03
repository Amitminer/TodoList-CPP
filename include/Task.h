#ifndef TASK_H
#define TASK_H

#include <string>

// Task class represents a single task with a description and a completion status.
class Task
{
public:
    // Constructor to initialize a Task with an id, description, and done status.
    Task(int id, const std::string &description, bool done);

    // Getter for the task ID.
    int getId() const;

    // Getter for the task description.
    std::string getDescription() const;

    // Check if the task is done.
    bool isDone() const;

    // Mark the task as done.
    void markDone();

private:
    int id;                  // Unique task ID
    std::string description; // Task description
    bool done;               // Task completion status
};

#endif // TASK_H
