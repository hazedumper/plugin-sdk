#pragma once

#include <hazedumper/plugin-sdk/dependencies.hpp>
#include "module_loader/module_loader_factory.hpp"
#include "log/log_factory.hpp"

namespace hazedumper::impl {
NODISCARD
inline
auto
make_dependency_container() noexcept -> dependencies_ptr
{
    return std::make_shared<dependencies>(
        make_module_loader(),
        std::make_shared<impl::log_factory>()
    );
}
}
