#pragma once

namespace hazedumper::detail {
struct version
{
    enum class state
    {
        ok,
        patch,
        minor,
        major,
    };

    u32 major{};
    u32 minor{};
    u32 patch{};

    constexpr
    version() noexcept = default;

    constexpr
    version(
        const u32 major,
        const u32 minor,
        const u32 patch
    ) noexcept
        : major(major)
        , minor(minor)
        , patch(patch)
    {}

    NODISCARD
    constexpr
    auto
    compare(
        const version& other
    ) const noexcept -> state
    {
        if (major > other.major) {
            return state::major;
        }

        if (minor > other.minor) {
            return state::minor;
        }

        if (patch > other.patch) {
            return state::patch;
        }

        return state::ok;
    }

    NODISCARD
    constexpr
    auto
    build() const noexcept -> u32
    {
        return major << 4 | minor << 2 | patch;
    }
};
}
