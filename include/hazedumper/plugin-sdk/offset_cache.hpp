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
        std::string_view group,
        std::string_view name,
        uptr             value
    ) -> void;
};
}
