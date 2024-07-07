#include "Task.h"

/**
 * @brief Constructs a Task object with specified attributes.
 *
 * @param id The unique identifier for the task.
 * @param description The description of the task.
 * @param done Boolean indicating whether the task is completed.
 * @param createdTime Timestamp when the task was created.
 * @param completedTime Timestamp when the task was completed (default: 0).
 */
Task::Task(int id, const std::string &description, bool done, time_t createdTime, time_t completedTime)
    : id(id), description(description), done(done), createdTime(createdTime), completedTime(completedTime) {
}

/**
 * @brief Destructor for cleaning up resources associated with the Task object.
 */
Task::~Task() {
}

/**
 * @brief Retrieves the unique identifier of the task.
 *
 * @return The ID of the task.
 */
int Task::getId() const {
    return id;
}

/**
 * @brief Retrieves the description of the task.
 *
 * @return The description of the task.
 */
std::string Task::getDescription() const {
    return description;
}

/**
 * @brief Checks if the task is marked as done.
 *
 * @return True if the task is marked as done, false otherwise.
 */
bool Task::isDone() const {
    return done;
}

/**
 * @brief Marks the task as done and updates the completion time to the current time.
 */
void Task::markDone() {
    done = true;
    completedTime = std::time(nullptr);
}

/**
 * @brief Retrieves the timestamp when the task was created.
 *
 * @return The creation time of the task.
 */
time_t Task::getCreatedTime() const {
    return createdTime;
}

/**
 * @brief Retrieves the timestamp when the task was completed.
 *
 * @return The completion time of the task.
 */
time_t Task::getCompletedTime() const {
    return completedTime;
}

/**
 * @brief Sets the completion time of the task.
 *
 * @param time The completion time to set.
 */
void Task::setCompletedTime(time_t time) {
    completedTime = time;
}
