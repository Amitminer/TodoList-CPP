#include <benchmark/benchmark.h>
#include "TaskManager.h"
#include "Database.h"

static void BM_AddTask(benchmark::State &state) {
    Database database("tasks_bench.db");
    TaskManager taskManager(database);
    std::string description = "Sample task description";

    // Perform setup (e.g., create initial tasks)
    taskManager.clearAllDataAsync().get(); // Clear all existing data before benchmark

    for (auto _ : state) {
        auto future = taskManager.addTaskAsync(description);
        future.wait();
    }
}
BENCHMARK(BM_AddTask);

static void BM_ListTasks(benchmark::State &state) {
    Database database("tasks_bench.db");
    TaskManager taskManager(database);

    for (auto _ : state) {
        auto future = taskManager.listTasksAsync();
        future.wait();
    }
}
// BENCHMARK(BM_ListTasks);

static void BM_MarkTaskDone(benchmark::State &state) {
    Database database("tasks_bench.db");
    TaskManager taskManager(database);

    // Perform setup (e.g., create initial tasks)
    taskManager.clearAllDataAsync().get(); // Clear all existing data before benchmark
    auto future = taskManager.addTaskAsync("Sample task");
    future.wait();

    int taskId = 1; // Assuming the task ID for the task added above

    for (auto _ : state) {
        auto markFuture = taskManager.markTaskDoneAsync(taskId);
        markFuture.wait();
    }
}
BENCHMARK(BM_MarkTaskDone);

static void BM_DeleteTask(benchmark::State &state) {
    Database database("tasks_bench.db");
    TaskManager taskManager(database);

    // Perform setup (e.g., create initial tasks)
    taskManager.clearAllDataAsync().get(); // Clear all existing data before benchmark
    auto future = taskManager.addTaskAsync("Sample task");
    future.wait();

    int taskId = 1; // Assuming the task ID for the task added above

    for (auto _ : state) {
        auto deleteFuture = taskManager.deleteTaskAsync(taskId);
        deleteFuture.wait();
    }
}
BENCHMARK(BM_DeleteTask);

static void BM_ClearAllData(benchmark::State &state) {
    Database database("tasks_bench.db");
    TaskManager taskManager(database);

    // Perform setup (e.g., create initial tasks)
    taskManager.clearAllDataAsync().get(); // Clear all existing data before benchmark

    for (auto _ : state) {
        taskManager.clearAllDataAsync().get(); // Clear all data repeatedly for benchmark
    }
}
BENCHMARK(BM_ClearAllData);

BENCHMARK_MAIN();
