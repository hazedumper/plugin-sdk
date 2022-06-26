#pragma once

#include "log.hpp"

namespace hazedumper {
ABSTRACT_CLASS(log_factory)
{
public:
    virtual
    ~log_factory() = default;

    virtual
    auto
    create(
        std::string_view name
    ) -> log_ptr = 0;

    virtual
    auto
    debug(
        bool active
    ) noexcept -> log_factory* = 0;

    virtual
    auto
    verbose(
        bool active
    ) noexcept -> log_factory* = 0;

    virtual
    auto
    info(
        bool active
    ) noexcept -> log_factory* = 0;

    virtual
    auto
    notice(
        bool active
    ) noexcept -> log_factory* = 0;
};
}
