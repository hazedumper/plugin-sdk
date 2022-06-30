#pragma once

#include "pattern.hpp"

namespace hazedumper {
ABSTRACT_CLASS(process)
{
protected:
    using map_images = std::map<szt, image_ptr>;

public:
    virtual
    ~process() = default;

    virtual
    auto
    attach(
        std::string_view name
    ) -> bool = 0;

    virtual
    auto
    attach(
        u32 pid
    ) -> bool = 0;

    virtual
    auto
    detach() noexcept -> void = 0;

    virtual
    auto
    get_image(
        std::string_view name,
        pattern::cache   cache_strategy = pattern::cache::hold_in_memory
    ) -> image_ptr = 0;

    virtual
    auto
    read_mem(
        uptr address,
        ptr  buffer,
        szt  size
    ) const noexcept -> void = 0;

    virtual
    auto
    write_mem(
        uptr address,
        cptr buffer,
        szt  size
    ) const noexcept -> void = 0;

    NODISCARD
    virtual
    auto
    x86() const noexcept -> bool = 0;

    NODISCARD
    constexpr
    auto
    id() const noexcept -> u32;

    template<typename T>
    auto
    read(
        uptr address,
        T*   buffer
    ) const noexcept -> void;

    template<typename T>
    auto
    read(
        uptr address,
        T&   buffer
    ) const noexcept -> void;

    template<typename T>
    auto
    read(
        uptr address
    ) const noexcept -> T;

    template<typename T>
    auto
    write(
        uptr address,
        T    buffer
    ) const noexcept -> void;

    template<typename T>
    NODISCARD
    auto
    resolve_call(
        uptr address,
        bool fix_displacement = false
    ) const noexcept -> uptr;

    template<typename T>
    NODISCARD
    auto
    resolve_jmp(
        uptr address,
        bool fix_displacement = false
    ) const noexcept -> uptr;

    NODISCARD
    auto
    resolve_rip(
        uptr address,
        bool fix_displacement = false
    ) const noexcept -> uptr;

protected:
    u32        id_{};
    map_images images_{};
};
}

#include <hazedumper/plugin-sdk/inl/process.inl>
