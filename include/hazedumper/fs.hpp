#pragma once

#include "plugin-sdk/prerequisites.hpp"

namespace hazedumper {
FINAL_CLASS(filesystem)
{
public:
    using enum_fn = std::function<void(const std::string&)>;

public:
    filesystem();

    auto
    enum_plugins(
        const enum_fn& callback
    ) const noexcept -> void;

    auto
    enum_scripts(
        const enum_fn& callback
    ) const noexcept -> void;

    NODISCARD
    auto
    root() const noexcept -> std::string_view
    {
        return directories_.root;
    }

    NODISCARD
    auto
    plugins() const noexcept -> std::string_view
    {
        return directories_.plugins;
    }

    NODISCARD
    auto
    scripts() const noexcept -> std::string_view
    {
        return directories_.scripts;
    }

private:
    struct
    {
        std::string root;
        std::string plugins;
        std::string scripts;
    } directories_{};
};
}
