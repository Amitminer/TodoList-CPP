#ifndef TASK_H
#define TASK_H

#include <string>
#include <ctime>

// Task class represents a single task with a description and a completion status.
class Task
{
public:
    // Constructor to initialize a Task with an id, description, and done status.
    Task(int id, const std::string &description, bool done, time_t createdTime, time_t completedTime);

    // Getter for the task ID.
    int getId() const;

    // Getter for the task description.
    std::string getDescription() const;

    // Check if the task is done.
    bool isDone() const;

    // Mark the task as done.
    void markDone();

    // Getter for the time when the task was created.
    time_t getCreatedTime() const;

    // Getter for the time when the task was completed.
    time_t getCompletedTime() const;

    // Setter for the time when the task was created.
    void setCompletedTime(time_t time);

private:
    int id;                  // Unique task ID
    std::string description; // Task description
    bool done;               // Task completion status
    time_t createdTime;      // Time when the task was created
    time_t completedTime;    // Time when the task was completed
};

#endif // TASK_H
