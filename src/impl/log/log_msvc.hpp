#pragma once

#include "abstract_log.hpp"

namespace hazedumper::impl {
FINAL_CLASS(log_msvc)
    : public abstract_log
{
    NODISCARD
    constexpr
    static
    auto
    get_color(
        const i32 level
    ) noexcept -> i32
    {
        switch (level) {
        case level_debug:
            return 12;
        case level_verbose:
            return 11;
        case level_info:
        case level_notice:
            return 10;
        case level_warning:
            return 6;
        default:
            break;
        }

        return 12;
    }

public:
    explicit
    log_msvc(
        std::string_view context
    ) noexcept;

    auto
    handle_message(
        i32              current_level,
        std::string_view message
    ) -> void override;
};
}
