#pragma once

#include <sys/ptrace.h>
#include <unistd.h>
#include <cstdint>

class breakpoint {
public:
    breakpoint(pid_t pid, std::intptr_t addres) 
        : pid_{pid}, address_{addres}, is_enabled_{false}, saved_data_{}
    { }

    void enable();
    void disable();

    auto is_enabled() const { return is_enabled_; }
    auto get_address() const { return address_; }

private:
    pid_t pid_;
    std::intptr_t address_;
    bool is_enabled_;
    uint8_t saved_data_;
};
