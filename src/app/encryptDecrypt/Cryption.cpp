#include <iostream>
#include "../processes/Task.hpp"
#include "../fileHandling/ReadEnv.cpp"

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: ./cryption <task_data>" << std::endl;
        return 1;
    }

    std::string taskData = argv[1];
    // Parse the task data and create a Task object
    Task task = Task::fromString(taskData);

    ReadEnv env;
    std::string envKey = env.getenv();
    int key = std::stoi(envKey);

    if (task.action == Action::ENCRYPT) {
        char ch;
        while (task.f_stream.get(ch)) {
            ch = (ch + key) % 256;
            task.f_stream.seekp(-1, std::ios::cur);
            task.f_stream.put(ch);
        }
        task.f_stream.close();
    } else {
        char ch;
        while (task.f_stream.get(ch)) {
            ch = (ch - key + 256) % 256;
            task.f_stream.seekp(-1, std::ios::cur);
            task.f_stream.put(ch);
        }
        task.f_stream.close();
    }

    return 0;
}