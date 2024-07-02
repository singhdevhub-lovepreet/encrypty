#include <iostream>
#include "ProcessManagement.hpp"
#include <unistd.h>
#include <cstring>
#include <sys/wait.h>
#include <vector>
#include "../encryptDecrypt/Cryption.hpp"

ProcessManagement::ProcessManagement() {}

bool ProcessManagement::submitToQueue(std::unique_ptr<Task> task) {
    taskQueue.push(std::move(task));
    return true;
}

void ProcessManagement::executeTasks() {
    while (!taskQueue.empty()) {
        // Add a breakpoint here in VS Code
        // int childProcessToRun = fork();
        // if (childProcessToRun == 0) {
        //     // Child process
        //     std::string taskStr = taskToExecute->toString();
        //     char* args[3];
        //     args[0] = strdup("./cryption");  // Use the correct path to your cryption executable
        //     args[1] = strdup(taskStr.c_str());
        //     args[2] = nullptr;
        //     execv("./cryption", args);  // Use the correct path to your cryption executable
        //     // If execv returns, there was an error
        //     std::cerr << "Error executing cryption" << std::endl;
        //     exit(1);
        // } else if (childProcessToRun > 0) {
        //     // Parent process
        //     // Wait for the child process to complete
        //     int status;
        //     waitpid(childProcessToRun, &status, 0);
        // } else {
        //     // Fork failed
        //     std::cerr << "Fork failed" << std::endl;
        //     exit(1);
        // }
        std::vector<pid_t> pids;
        while(!taskQueue.empty()){
            std::unique_ptr<Task> taskToExecute = std::move(taskQueue.front());
            taskQueue.pop();
            pid_t childprocess = fork();
            if(childprocess == 0) {
                std::string taskstr = taskToExecute->toString();
                std::cout << "child process " << getpid() << " running the task " << taskstr << std::endl;
                char *args[3];
                args[0] = strdup("./cryption");
                args[1] = strdup(taskstr.c_str());
                args[2] = nullptr;
                if(execv("./cryption", args) == -1) {
                    perror("execv failed");
                    free(args[0]);
                    free(args[1]);
                }
                free(args[0]);
                free(args[1]);
            } else if (childprocess > 0) {
                // wait state
                std::cout << "Parent called child process " << childprocess << std::endl;
                pids.push_back(childprocess);
            } else {
                std::cerr << "Fork Failed" << std::endl;
                exit(1);
            }
        }
        
        for (pid_t childPid : pids) {
            int status;
            waitpid(childPid, &status, 0);
            if (WIFEXITED(status)) {
                std::cout << "Child process " << childPid << " exited with status " << WEXITSTATUS(status) << std::endl;
            } else {
                std::cout << "Child process " << childPid << " terminated abnormally" << std::endl;
            }
        }
    }
}