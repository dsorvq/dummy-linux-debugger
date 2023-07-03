#pragma once

#include <cstdint>
#include <unistd.h>
#include <string>
#include <string_view>
#include <charconv>
#include <vector>
#include <unordered_map>
#include <iostream>
#include <sys/wait.h>
#include <sys/ptrace.h>

#include <linenoise.h>

#include "breakpoint.hpp"

class debugger {
public:
    debugger(std::string program_name, pid_t pid) 
        : program_name_{program_name}, pid_{pid}
    {}
    
    void set_breakpoint(std::intptr_t address);

    void run();
    void handle_command(std::string_view line);
    void continue_execution();

private:
    std::string program_name_;
    pid_t pid_;
    std::unordered_map<std::intptr_t, breakpoint> breakpoints_;
};

