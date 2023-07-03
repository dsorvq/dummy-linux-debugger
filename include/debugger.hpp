#pragma once

#include <unistd.h>
#include <string>
#include <string_view>
#include <vector>
#include <iostream>
#include <sys/wait.h>
#include <sys/ptrace.h>

#include "linenoise.h"

class debugger {
public:
    debugger(std::string program_name, pid_t pid) 
        : program_name_{program_name}, pid_{pid}
    {}
    
    void run();
    void handle_command(std::string_view line);
    void continue_execution();

private:
    std::string program_name_;
    pid_t pid_;
};

