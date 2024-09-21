#ifndef PROCESS_MANAGEMENT_HPP
#define PROCESS_MANAGEMENT_HPP

#include "Task.hpp"
#include <memory>
#include <mutex>
#include <atomic>
#include <semaphore.h>
#include <iostream>  

class ProcessManagement
{
public:
    ProcessManagement();
    ~ProcessManagement();

    bool submitToQueue(std::unique_ptr<Task> task);
    void executeTask();

private:
    struct SharedMemory {
        std::atomic<int> size;
        char tasks[1000][256];
        std::atomic<int> front;
        std::atomic<int> rear;

        void printSharedMemory() {
            std::cout << "Size: " << size.load() << std::endl;
            std::cout << "Front: " << front.load() << std::endl;
            std::cout << "Rear: " << rear.load() << std::endl;
        }
    };

    SharedMemory* sharedMem;       
    int shmFd;                     

    sem_t* itemsSemaphore;
    sem_t* emptySlotsSemaphore;    

    const char* SHM_NAME = "/my_queue"; 

    std::mutex queueLock;
};

#endif 