#ifndef PROCESS_MANAGEMENT_HPP
#define PROCESS_MANAGEMENT_HPP

#include "Task.hpp"
#include <queue>
#include <memory>
#include <semaphore.h>

class ProcessManagement
{
public:
    ProcessManagement();
    bool submitToQueue(std::unique_ptr<Task> task);
    void executeTask();

private:
    struct SharedMemory {
        int size;
        char tasks[1000][256];
        int front;
        int rear;
    };
    SharedMemory* sharedMem;
    int shmFd;
    const char* SHM_NAME = "/my_queue";
};

#endif