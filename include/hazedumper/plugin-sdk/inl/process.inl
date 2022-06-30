#pragma once

namespace hazedumper {
constexpr
auto process::id() const noexcept -> u32
{
    return id_;
}

template<typename T>
auto
process::read(
    const uptr address,
    T* const   buffer
) const noexcept -> void
{
    read_mem(address, buffer, sizeof(T));
}

template<typename T>
auto
process::read(
    const uptr address,
    T& buffer
) const noexcept -> void
{
    read_mem(address, &buffer, sizeof(T));
}

template<typename T>
auto
process::read(
    const uptr address
) const noexcept -> T
{
    T buf{};

    read(address, buf);

    return buf;
}

template<typename T>
auto
process::write(
    const uptr address,
    const T    buffer
) const noexcept -> void
{
    if constexpr (std::is_pointer_v<T>) {
        write_mem(
            address, 
            buffer, 
            sizeof(std::remove_pointer_t<T>)
        );
    } else {
        write_mem(address, &buffer, sizeof(T));
    }
}

template<typename T>
auto
process::resolve_call(
    const uptr address,
    const bool fix_displacement
) const noexcept -> uptr
{
    static_assert(
        std::is_same_v<T, i64> ||
        std::is_same_v<T, u64> ||
        std::is_same_v<T, i32> ||
        std::is_same_v<T, u32>,
        "Type T must be i32, u32, i64, u64, iptr or uptr"
    );

    if (!address || read<u8>(address) != 0xE8) {
        return 0;
    }

    if constexpr (sizeof(T) == sizeof(u32)) {
        return address + read<u32>(address + 1) + 5;
    }

    return resolve_rip(address + 1, fix_displacement);
}

template<typename T>
auto
process::resolve_jmp(
    const uptr address,
    const bool fix_displacement
) const noexcept -> uptr
{
    static_assert(
        std::is_same_v<T, i64> ||
        std::is_same_v<T, u64> ||
        std::is_same_v<T, i32> ||
        std::is_same_v<T, u32>,
        "Type T must be i32, u32, i64, u64, iptr or uptr"
    );

    if (!address) {
        return 0;
    }

    const auto opcode{ read<u8>(address) };

    if constexpr (sizeof(T) == sizeof(u32)) {
        const auto jmp_short = opcode == 0xEB;
        const auto jmp_near = opcode == 0xE9;

        return jmp_short || jmp_near
            ? address + read<u32>(address + 1) + (jmp_short ? 2 : 5)
            : 0;
    }

    return opcode == 0xE9
        ? resolve_rip(address + 1, fix_displacement)
        : 0;
}

inline
auto
process::resolve_rip(
    const uptr address,
    const bool fix_displacement
) const noexcept -> uptr
{
    if (!fix_displacement) {
        const auto data{ read<u32>(address) };

        return data
            ? address + 4 + data
            : 0;
    }

    const auto displacement{ read<u32>(address + 1) };
    auto       result{ address + displacement + 5 };

    if (displacement & 0x80000000) {
        result -= 0x100000000;
    }

    return result;
}
}
