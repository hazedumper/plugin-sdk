#pragma once

#include <hazedumper/plugin-sdk/prerequisites.hpp>

namespace hazedumper::lua {
enum class call_state : u32
{
    success,
    yield,
    runtime,
    syntax,
    mem_alloc,
    error,
    file,
};
}
