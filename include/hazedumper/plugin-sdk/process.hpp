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
    constexpr
    auto
    id() const noexcept -> u32
    {
        return id_;
    }

    template<typename T>
    auto
    read(
        const uptr address,
        T* const   buffer
    ) const noexcept -> void
    {
        read_mem(address, buffer, sizeof(T));
    }

    template<typename T>
    auto
    read(
        const uptr address,
        T&         buffer
    ) const noexcept -> void
    {
        read_mem(address, &buffer, sizeof(T));
    }    

    template<typename T>
    auto
    read(
        const uptr address
    ) const noexcept -> T
    {
        T buf{};

        read(address, buf);

        return buf;
    }

    template<typename T>
    auto
    write(
        const uptr address,
        const T    buffer
    ) const noexcept -> void
    {
        if constexpr (std::is_pointer_v<T>) {
            write_mem(address, buffer, sizeof(std::remove_pointer_t<T>));
        } else {
            write_mem(address, &buffer, sizeof(T));
        }
    }

protected:
    u32        id_{};
    map_images images_{};
};
}
