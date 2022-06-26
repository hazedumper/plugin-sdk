#pragma once

#include "prerequisites.hpp"
#include <sstream>

namespace hazedumper {
FINAL_CLASS(pattern)
{
public:
    enum class cache
    {
        fetch,
        hold_in_memory,
    };

    using update_cache_fn = std::function<void(const pattern*, raw_t&)>;

private:
    NODISCARD
    constexpr
    static
    auto
    cmp_opcode(
        const u8*   code,
        const u8*   pattern,
        const char* mask
    ) noexcept -> bool
    {
        for (; *mask; ++mask, ++code, ++pattern) {
            if (*mask == 'x' && *code != *pattern) {
                return false;
            }
        }

        return *mask == 0;
    }

public:
    pattern(
        const uptr  base,
        const szt   size,
        const cache cache_strategy
    ) noexcept
        : base_(base)
        , size_(size)
        , cache_strategy_(cache_strategy)
    {
        if (cache_strategy == cache::hold_in_memory) {
            update_cache_(this, buffer_);
        }
    }

    NODISCARD
    constexpr
    auto
    base() const noexcept -> uptr
    {
        return base_;
    }

    NODISCARD
    constexpr
    auto
    size() const noexcept -> szt
    {
        return size_;
    }

    NODISCARD
    constexpr
    auto
    cache_strategy() const noexcept -> cache
    {
        return cache_strategy_;
    }

    NODISCARD
    auto
    scan(
        const u8* const        pattern,
        const std::string_view mask
    ) const -> uptrs
    {
        if (!pattern || mask.empty() || !base_ || !size_) {
            return {};
        }

        const auto* buffer_ptr{ &buffer_ };
        raw_t       local_buffer{};

        if (cache_strategy_ == cache::fetch) {
            update_cache_(this, local_buffer);

            buffer_ptr = &local_buffer;
        }

        const auto mask_raw{ mask.data() };
        const auto buffer{ buffer_ptr->data() };
        const auto length{ buffer_ptr->size() - mask.length() };
        uptrs      result;

        for (szt i{}; i < length; ++i) {
            if (cmp_opcode(buffer, pattern, mask_raw)) {
                result.push_back(base_ + i);
            }
        }

        return result;
    }

    NODISCARD
    auto
    scan(
        const std::string_view signature
    ) const -> uptrs
    {
        std::istringstream iss(signature.data());

        if (!iss) {
            return {};
        }

        std::string current, mask;
        raw_t       pattern{};

        while (std::getline(iss, current, ' ')) {
            if (current.empty()) {
                continue;
            }

            const auto is_unknown{
                current.find('?') != std::string::npos
            };

            mask += (is_unknown ? '?' : 'x');

            pattern.push_back(
                static_cast<u8>(
                    is_unknown 
                        ? 0
                        : std::strtoul(
                            current.data(), 
                            nullptr, 
                            16
                        )
                )
            );
        }

        return scan(pattern.data(), mask);
    }

    static
    auto
    set_update_cache_routine(
        update_cache_fn callback
    ) noexcept -> void
    {
        update_cache_ = std::move(callback);
    }

private:
    static inline
    update_cache_fn update_cache_;
    uptr            base_;
    szt             size_;
    raw_t           buffer_;
    cache           cache_strategy_;
};
}
