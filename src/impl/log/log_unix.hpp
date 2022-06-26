#pragma once

#include "abstract_log.hpp"

namespace hazedumper::impl {
FINAL_CLASS(log_unix)
    : public abstract_log
{
    NODISCARD
    static
    auto
    get_color(
        i32 level
    ) noexcept -> std::string_view;

public:
    explicit
    log_unix(
        std::string_view context
    ) noexcept;

    auto
    handle_message(
        i32              current_level,
        std::string_view message
    ) -> void override;
};
}