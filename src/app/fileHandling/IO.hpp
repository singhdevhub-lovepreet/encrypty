#ifndef IOFILE_HANDLING
#define IOFILE_HANDLING
#include <fstream>
#include <string>

class IO{
    public: 
        IO(const std::string &file_path);
        ~IO();

        std::fstream& getFileStream(); 

    private: 
        std::fstream file_stream;
};

#endif