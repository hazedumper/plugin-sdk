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
};
}
