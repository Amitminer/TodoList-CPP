#include "Task.h"
#include <ctime> // For time_t and time functions

/**
 * @brief Construct a new Task object with the specified parameters.
 *
 * Initializes a task with an ID, description, completion status, creation time, and completion time.
 *
 * @param id Task ID.
 * @param description Task description.
 * @param done Task completion status.
 * @param createdTime Timestamp when the task was created.
 * @param completedTime Timestamp when the task was completed.
 */
Task::Task(int id, const std::string &description, bool done, time_t createdTime, time_t completedTime)
    : id(id), description(description), done(done), createdTime(createdTime), completedTime(completedTime) {}

/**
 * @brief Get the task's ID.
 *
 * @return Task ID.
 */
int Task::getId() const
{
    return id;
}

/**
 * @brief Get the task's description.
 *
 * @return Task description.
 */
std::string Task::getDescription() const
{
    return description;
}

/**
 * @brief Check if the task is done.
 *
 * @return True if the task is done, false otherwise.
 */
bool Task::isDone() const
{
    return done;
}

/**
 * @brief Mark the task as done and set the completion time to the current time.
 */
void Task::markDone()
{
    done = true;
    completedTime = std::time(nullptr); // Set completed time to current time
}

/**
 * @brief Get the time when the task was created.
 *
 * @return Creation time as a timestamp.
 */
time_t Task::getCreatedTime() const
{
    return createdTime;
}

/**
 * @brief Get the time when the task was completed.
 *
 * @return Completion time as a timestamp.
 */
time_t Task::getCompletedTime() const
{
    return completedTime;
}

/**
 * @brief Set the time when the task was completed.
 *
 * @param time Completion time as a timestamp.
 */
void Task::setCompletedTime(time_t time)
{
    completedTime = time;
}
