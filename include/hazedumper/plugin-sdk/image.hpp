#pragma once

#include "pattern.hpp"

namespace hazedumper {
FINAL_CLASS(image)
{
public:
    image(
        const std::string_view name,
        const uptr             base,
        const szt              size,
        const pattern::cache   cache_strategy
    ) noexcept
        : pattern_(base, size, cache_strategy)
        , name_(name)
    {}

    NODISCARD
    auto
    name() const noexcept -> std::string_view
    {
        return name_;
    }

    NODISCARD
    constexpr
    auto
    base() const noexcept -> uptr
    {
        return pattern_.base();
    }

    NODISCARD
    constexpr
    auto
    size() const noexcept -> szt
    {
        return pattern_.size();
    }

    NODISCARD
    auto
    pattern() noexcept -> hazed::pattern&
    {
        return pattern_;
    }

    NODISCARD
    constexpr
    auto
    pattern() const noexcept -> const hazed::pattern&
    {
        return pattern_;
    }

private:
    hazed::pattern pattern_;
    std::string    name_;
};
}
