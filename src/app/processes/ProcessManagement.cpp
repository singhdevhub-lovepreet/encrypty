#include <iostream>
#include "ProcessManagement.hpp"
#include <unistd.h>
#include <cstring>
#include <sys/wait.h>
#include "../encryptDecrypt/Cryption.hpp"

ProcessManagement::ProcessManagement() {}

bool ProcessManagement::submitToQueue(std::unique_ptr<Task> task) {
    taskQueue.push(std::move(task));
    int pid = fork();
    if(pid < 0){
        return false;
    }else if(pid > 0){
        std::cout<<"Entering the parent process"<<std::endl;
    }else{
        std::cout<<"Entering the child process"<<std::endl; 
        executeTask();
        std::cout<<"Exiting the child process"<<std::endl;
    }
    return true;
}

void ProcessManagement::executeTask() {
    
    if(!taskQueue.empty()){
        std::unique_ptr<Task> task = std::move(taskQueue.front());
        taskQueue.pop();
        std::cout<<"Executing task: "<<task->toString()<<std::endl;
        executeCryption(task->toString());
    }

}