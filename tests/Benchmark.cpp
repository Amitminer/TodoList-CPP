#include <benchmark/benchmark.h>
#include "TaskManager.h"
#include "Database.h"

static void BM_AddTask(benchmark::State &state)
{
    Database database("tasks2.db");
    TaskManager taskManager(database);
    std::string description = "Sample task description";

    for (auto _ : state)
    {
        taskManager.addTask(description);
    }
}
BENCHMARK(BM_AddTask);

// todo: add more tests

BENCHMARK_MAIN();
