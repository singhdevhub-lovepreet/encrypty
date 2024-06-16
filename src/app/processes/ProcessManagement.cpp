#include <iostream>
#include "ProcessManagement.hpp"
#include <unistd.h>
#include <cstring>

ProcessManagement::ProcessManagement() {}

bool ProcessManagement::submitToQueue(std::unique_ptr<Task> task) {
    taskQueue.push(std::move(task));
}

void ProcessManagement::executeTasks() {
    while (!taskQueue.empty()) {
        std::unique_ptr<Task> taskToExecute = std::move(taskQueue.front());
        taskQueue.pop();

        int childProcessToRun = fork();
        if (childProcessToRun == 0) {
            // Child process
            char* args[2];
            args[0] = strdup("cryption.o");
            args[1] = nullptr;

            // Convert the task object to a string representation
            std::string taskStr = taskToExecute->toString();

            // Set the task string as an environment variable
            setenv("TASK_DATA", taskStr.c_str(), 1);

            // Execute the cryption.o object file
            execv("cryption.o", args);

            // If execv returns, there was an error
            std::cerr << "Error executing cryption.o" << std::endl;
            exit(1);
        } else if (childProcessToRun > 0) {
            // Parent process
            // Wait for the child process to complete
            int status;
            waitpid(childProcessToRun, &status, 0);
        } else {
            // Fork failed
            std::cerr << "Fork failed" << std::endl;
            exit(1);
        }
    }
}