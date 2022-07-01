#pragma once

#include <hazedumper/plugin-sdk/prerequisites.hpp>

namespace hazedumper {
ABSTRACT_CLASS(offset_cache)
{
protected:
    using enum_fn = std::function<
        void(const std::string&, const std::string&, uptr)
    >;

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

    virtual
    auto
    enumerate(
        HAZEDUMPER_CONST_REF(enum_fn) callback
    ) const -> void = 0;
};
}
