#include "debugger.hpp"

void debugger::run() {
    int wait_status{};
    int options{};
    waitpid(pid_, &wait_status, options);

    char* line{nullptr};
    while ((line = linenoise("dummy-dbg> "))) {
        handle_command(line);
        linenoiseHistoryAdd(line);
        linenoiseFree(line);
    }
}

void debugger::set_breakpoint(std::intptr_t address) {
    std::cout << "Set breakpoint at 0x" << std::hex << address << '\n';
    breakpoint bp{pid_, address};
    bp.enable();
    breakpoints_[address] = bp;
}

std::vector<std::string_view> split(
        std::string_view str, 
        std::string_view delim) 
{
    std::vector<std::string_view> ans;

    auto n = str.size();
    int l = 0;
    while (l < n) {
        auto r = str.find_first_of(delim, l);
        if (l != r)
            ans.emplace_back(str.substr(l, r - l));
        if (r == str.npos)
            break;
        l = r + 1;
    }

    return ans;
}

void debugger::handle_command(std::string_view line) {
    auto args = split(line, " ");
    auto command = args[0];

    if (std::string_view("continue").starts_with(command)) {
        continue_execution();
    }
    else if (std::string_view("break").starts_with(command)) {
        auto addr_sv {args[1].substr(2)};

        unsigned long long address;
        std::from_chars(addr_sv.data() + 2, addr_sv.data() + addr_sv.size(), address);
        set_breakpoint(address);
    }
    else {
        std::cerr << "Unknowd command\n";
    }
}

void debugger::continue_execution() {
    ptrace(PTRACE_CONT, pid_, nullptr, nullptr);

    int wait_status{};
    int options{};
    waitpid(pid_, &wait_status, options);
}
