#ifndef PROCESS_MANAGEMENT_HPP
#define PROCESS_MANAGEMENT_HPP

#include "Task.hpp"
#include <queue>

class ProcessManagement
{
    public:
        ProcessManagement();
        bool submitToQueue(Task &task);
        void processQueue(); 
    private: 
        std::queue<Task> taskQueue;
        void executeTasks(const Task &task);
};

#endif