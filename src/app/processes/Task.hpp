#ifndef TASK_HPP
#define TASK_HPP

#include <fstream>

enum class Action {
    ENCRYPT,
    DECRYPT
};

struct Task {
    std::fstream f_stream;
    Action action;
    Task(std::fstream &&stream, Action act) : f_stream(std::move(stream)), action(act) {}
};


#endif