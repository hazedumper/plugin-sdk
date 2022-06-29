#pragma once

#include <hazedumper/plugin-sdk/prerequisites.hpp>

namespace hazedumper {
ABSTRACT_CLASS(filesystem)
{
public:
    using enum_fn = std::function<void(const std::string&)>;

public:
    virtual
    ~filesystem() = default;

    virtual
    auto
    enum_plugins(
        const enum_fn& callback
    ) const noexcept -> void = 0;

    virtual
    auto
    enum_scripts(
        const enum_fn& callback
    ) const noexcept -> void = 0;

    NODISCARD
    virtual
    auto
    parent(
        std::string_view dir
    ) const -> std::string = 0;

    virtual
    auto
    mkdir(
        std::string_view dir
    ) const -> void = 0;

    NODISCARD
    virtual
    auto
    has_extension(
        std::string_view file,
        std::string_view extension
    ) const noexcept -> bool = 0;
    
    virtual
    auto
    strip_path(
        std::string& filename
    ) const -> void = 0;

    NODISCARD
    virtual
    auto
    root() const noexcept -> std::string_view = 0;

    NODISCARD
    virtual
    auto
    plugins() const noexcept -> std::string_view = 0;

    NODISCARD
    virtual
    auto
    scripts() const noexcept -> std::string_view = 0;
};
}
