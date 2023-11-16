#include <sys/ptrace.h>
#include <unistd.h>

#include <iostream>

#include "debugger.hpp"

int main(int argc, char* argv[]) {
  if (argc < 2) {
    std::cerr << "No program was scepified\n";
    return -1;
  }

  auto program = argv[1];

  auto pid = fork();
  if (pid == 0) {
    ptrace(PTRACE_TRACEME, 0, nullptr, nullptr);
    execl(program, program, nullptr);
  } else if (pid > 0) {
    std::cout << "Started debuggin of " << pid << '\n';

    debugger dbg{program, pid};
    dbg.run();
  }
}
