#include <iostream>
#include "ProcessManagement.hpp";

ProcessManagement::ProcessManagement(){}

bool ProcessManagement::submitToQueue(Task &task){
    taskQueue.push(task);
}