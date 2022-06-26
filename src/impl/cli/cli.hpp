#pragma once

#include <hazedumper/plugin-sdk/prerequisites.hpp>

namespace hazedumper::impl {
NODISCARD
auto
command_line(
    i32          argc,
    const char** argv
) -> i32;
}
