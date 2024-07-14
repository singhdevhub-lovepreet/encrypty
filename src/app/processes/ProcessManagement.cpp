#include <iostream>
#include "ProcessManagement.hpp"
#include <unistd.h>
#include <cstring>
#include <sys/wait.h>
#include "../encryptDecrypt/Cryption.hpp"
#include <sys/mman.h>


ProcessManagement::ProcessManagement() {

    shmFd = shm_open(SHM_NAME, O_CREAT | O_RDWR, 0666);
    ftruncate(shmFd, sizeof(SharedMemory));
    sharedMem = (SharedMemory*)mmap(0, sizeof(SharedMemory), PROT_READ | PROT_WRITE, MAP_SHARED, shmFd, 0);
    sharedMem->front = sharedMem->rear = sharedMem->size = 0;

}

bool ProcessManagement::submitToQueue(std::unique_ptr<Task> task) {
    
    strcpy(sharedMem->tasks[sharedMem->rear], task->toString().c_str());
    sharedMem->rear = (sharedMem->rear + 1) % 1000;
    sharedMem->size++;

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
    
    if(sharedMem->size > 0){
        char taskStr[256];
        strcpy(taskStr, sharedMem->tasks[sharedMem->front]);
        sharedMem->front = (sharedMem->front + 1) % 1000;
        sharedMem->size--;
        
        std::cout<<"Executing task: "<<taskStr<<std::endl;
        executeCryption(taskStr);
    }

}

ProcessManagement::~ProcessManagement() {
    munmap(sharedMem, sizeof(SharedMemory));
    shm_unlink(SHM_NAME);
}