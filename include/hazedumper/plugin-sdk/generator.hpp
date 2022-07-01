#pragma once

#include <hazedumper/plugin-sdk/prerequisites.hpp>

namespace hazedumper {
ABSTRACT_CLASS(generator)
{
public:
    virtual
    ~generator() = default;

    NODISCARD
    virtual
    auto
    extension() const noexcept -> std::string_view = 0;

    virtual
    auto
    build(
        const std::string& group,
        const std::string& name,
        uptr               value
    ) -> void = 0;

    NODISCARD
    virtual
    auto
    result() const -> std::string = 0;
};
}
