#include "Task.h"

// Initialize the task with the given id, description, and done status.
Task::Task(int id, const std::string &description, bool done)
    : id(id), description(description), done(done) {}

// Return the task's ID.
int Task::getId() const
{
    return id;
}

// Return the task's description.
std::string Task::getDescription() const
{
    return description;
}

// Return whether the task is done.
bool Task::isDone() const
{
    return done;
}

// Mark the task as done.
void Task::markDone()
{
    done = true;
}
