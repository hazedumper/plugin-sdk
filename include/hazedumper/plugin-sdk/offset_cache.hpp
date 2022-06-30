#pragma once

#include <hazedumper/plugin-sdk/prerequisites.hpp>

namespace hazedumper {
ABSTRACT_CLASS(offset_cache)
{
public:
    virtual
    ~offset_cache() = default;

    virtual
    auto
    add(
        const std::string& group,
        const std::string& name,
        uptr               value
    ) -> void = 0;
};
}
