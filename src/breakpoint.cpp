#include "breakpoint.hpp"

void breakpoint::enable() {
    auto data = ptrace(PTRACE_PEEKDATA, pid_, address_, nullptr);
    saved_data_ = static_cast<uint8_t>(data & 0xff);
    const uint64_t int3 = 0xcc;
    auto data_with_int3 = ((data & ~0xff) | int3);
    ptrace(PTRACE_POKEDATA, pid_, address_, data_with_int3);

    is_enabled_ = true;
}

void breakpoint::disable() {
    auto data = ptrace(PTRACE_PEEKDATA, pid_, address_, nullptr);
    auto restored_data = ((data & ~0xff) | saved_data_);
    ptrace(PTRACE_POKEDATA, pid_, address_, restored_data);

    is_enabled_ = false;
}
