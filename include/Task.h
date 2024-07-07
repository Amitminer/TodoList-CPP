#ifndef TASK_H
#define TASK_H

#include <string>
#include <ctime>

/**
 * @brief Represents a Task in the Todo List.
 *
 * This class encapsulates information about a task, including its ID, description,
 * completion status, and timestamps for creation and completion.
 */
class Task {
private:
    int id;                  ///< Unique identifier for the task.
    std::string description; ///< Description of the task.
    bool done;               ///< Flag indicating whether the task is completed.
    time_t createdTime;      ///< Timestamp indicating when the task was created.
    time_t completedTime;    ///< Timestamp indicating when the task was completed.

public:
    /**
     * @brief Constructor to initialize a Task object.
     *
     * @param id The unique identifier for the task.
     * @param description The description of the task.
     * @param done Boolean indicating whether the task is completed.
     * @param createdTime Timestamp when the task was created.
     * @param completedTime Timestamp when the task was completed (default: 0).
     */
    Task(int id, const std::string &description, bool done, time_t createdTime, time_t completedTime = 0);

    /**
     * @brief Destructor to clean up resources associated with the Task.
     */
    ~Task();

    /**
     * @brief Gets the unique identifier of the task.
     *
     * @return The ID of the task.
     */
    int getId() const;

    /**
     * @brief Gets the description of the task.
     *
     * @return The description of the task.
     */
    std::string getDescription() const;

    /**
     * @brief Checks if the task is completed.
     *
     * @return True if the task is completed, false otherwise.
     */
    bool isDone() const;

    /**
     * @brief Marks the task as done and sets the completion time.
     */
    void markDone();

    /**
     * @brief Gets the timestamp when the task was created.
     *
     * @return The creation time of the task.
     */
    time_t getCreatedTime() const;

    /**
     * @brief Gets the timestamp when the task was completed.
     *
     * @return The completion time of the task.
     */
    time_t getCompletedTime() const;

    /**
     * @brief Sets the completion time of the task.
     *
     * @param time The completion time to set.
     */
    void setCompletedTime(time_t time);
};

#endif // TASK_H
