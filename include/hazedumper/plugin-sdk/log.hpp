#pragma once

#include "prerequisites.hpp"

namespace hazedumper {
ABSTRACT_CLASS(log)
{
protected:
    enum
    {
        level_none    = 0,
        level_debug   = 1 << 0,
        level_verbose = 1 << 1,
        level_info    = 1 << 2,
        level_notice  = 1 << 3,
        level_warning = 1 << 4,
        level_error   = 1 << 5,
    };

    template<szt N, typename ...Args>
    auto
    forward_message_for_level(
        const i32         current_level,
        const char* const fmt,
        const Args&       ...args
    ) -> log*
    {
        if (!!(levels() & current_level)) {
            char buffer[N + 1]{};

        #if defined(HAZEDUMPER_MSVC)
            sprintf_s(buffer, N + 1, fmt, args...);
        #else
            std::sprintf(buffer, fmt, args...);
        #endif

            
            handle_message(current_level, buffer);
        }

        return this;
    }

    virtual
    auto
    handle_message(
        i32              current_level,
        std::string_view message
    ) -> void = 0;

public:
    virtual
    ~log() = default;

    NODISCARD
    virtual
    auto
    levels() const noexcept -> i32 = 0;

    virtual
    auto
    new_line(
        bool active
    ) noexcept -> log* = 0;

    virtual
    auto
    debug(
        bool active
    ) noexcept -> log* = 0;

    virtual
    auto
    verbose(
        bool active
    ) noexcept -> log* = 0;

    virtual
    auto
    info(
        bool active
    ) noexcept -> log* = 0;

    virtual
    auto
    notice(
        bool active
    ) noexcept -> log* = 0;

    virtual
    auto
    warning(
        bool active
    ) noexcept -> log* = 0;

    virtual
    auto
    error(
        bool active
    ) noexcept -> log* = 0;

    virtual
    auto
    show_names(
        bool active
    ) noexcept -> log* = 0;

    virtual
    auto
    show_pid(
        bool active
    ) noexcept -> log* = 0;

    template<szt N = 512, typename ...Args>
    auto
    debug(
        const char* const fmt,
        const Args&       ...args
    ) -> log*
    {
        return forward_message_for_level<N>(level_debug, fmt, args...);
    }

    template<szt N = 512, typename ...Args>
    auto
    verbose(
        const char* const fmt,
        const Args&       ...args
    ) -> log*
    {
        return forward_message_for_level<N>(level_verbose, fmt, args...);
    }

    template<szt N = 512, typename ...Args>
    auto
    info(
        const char* const fmt,
        const Args&       ...args
    ) -> log*
    {
        return forward_message_for_level<N>(level_info, fmt, args...);
    }

    template<szt N = 512, typename ...Args>
    auto
    notice(
        const char* const fmt,
        const Args&       ...args
    ) -> log*
    {
        return forward_message_for_level<N>(level_notice, fmt, args...);
    }

    template<szt N = 512, typename ...Args>
    auto
    warning(
        const char* const fmt,
        const Args&       ...args
    ) -> log*
    {
        return forward_message_for_level<N>(level_warning, fmt, args...);
    }

    template<szt N = 512, typename ...Args>
    auto
    error(
        const char* const fmt,
        const Args&       ...args
    ) -> log*
    {
        return forward_message_for_level<N>(level_error, fmt, args...);
    }
};
}
