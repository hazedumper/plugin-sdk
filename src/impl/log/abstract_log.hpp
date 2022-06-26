#pragma once

#include <hazedumper/plugin-sdk/log.hpp>

namespace hazedumper::impl {
ABSTRACT_CLASS(abstract_log)
    : public log
{
    using map_level_names = std::map<i32, std::string_view>;

    auto
    handle_level_flag(
        const bool active,
        const i32  flag
    ) noexcept -> log*
    {
        if (active) {
            levels_ |= flag;
        } else {
            levels_ &= ~flag;
        }

        return this;
    }

public:
    abstract_log(
        const std::string_view context,
        const u32              pid
    ) noexcept
        : context_(context)
        , process_id_(pid)
    {}

    NODISCARD
    auto
    levels() const noexcept -> i32 override
    {
        return levels_;
    }

    auto
    new_line(
        const bool active
    ) noexcept -> log* override
    {
        new_line_ = active;

        return this;
    }

    auto
    debug(
        const bool active
    ) noexcept -> log* override
    {
        return handle_level_flag(active, level_debug);
    }

    auto
    verbose(
        const bool active
    ) noexcept -> log* override
    {
        return handle_level_flag(active, level_verbose);
    }

    auto
    info(
        const bool active
    ) noexcept -> log* override
    {
        return handle_level_flag(active, level_info);
    }

    auto
    notice(
        const bool active
    ) noexcept -> log* override
    {
        return handle_level_flag(active, level_notice);
    }

    auto
    warning(
        const bool active
    ) noexcept -> log* override
    {
        return handle_level_flag(active, level_warning);
    }

    auto
    error(
        const bool active
    ) noexcept -> log* override
    {
        return handle_level_flag(active, level_error);
    }

protected:
    std::string context_;
    u32         process_id_;
    i32         levels_{ level_warning | level_error };
    bool        new_line_{ true };

    static inline
    map_level_names level_names_ = {
        { level_debug,   "DEBUG" },
        { level_verbose, "VERBOSE" },
        { level_info,    "INFO" },
        { level_notice,  "NOTICE" },
        { level_warning, "WARNING" },
        { level_error,   "ERROR" },
    };
};
}
