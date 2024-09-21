#ifndef PROCESS_MANAGEMENT_HPP
#define PROCESS_MANAGEMENT_HPP

#include "Task.hpp"
#include <memory>
#include <mutex>
#include <atomic>
#include <semaphore.h>
#include <iostream>  // Required for std::cout in printSharedMemory

class ProcessManagement
{
public:
    ProcessManagement();
    ~ProcessManagement();

    bool submitToQueue(std::unique_ptr<Task> task);
    void executeTask();

private:
    struct SharedMemory {
        std::atomic<int> size;    // Number of tasks in the queue
        char tasks[1000][256];    // Task queue
        std::atomic<int> front;   // Queue front
        std::atomic<int> rear;    // Queue rear

        // Helper function to print the state of the shared memory
        void printSharedMemory() {
            std::cout << "Size: " << size.load() << std::endl;
            std::cout << "Front: " << front.load() << std::endl;
            std::cout << "Rear: " << rear.load() << std::endl;
        }
    };

    SharedMemory* sharedMem;       // Pointer to shared memory
    int shmFd;                     // Shared memory file descriptor

    sem_t* itemsSemaphore;         // Semaphore to track items in the queue
    sem_t* emptySlotsSemaphore;    // Semaphore to track empty slots in the queue

    const char* SHM_NAME = "/my_queue"; // Name for the shared memory object

    std::mutex queueLock;          // Mutex to protect shared memory access
};

#endif // PROCESS_MANAGEMENT_HPP
