#pragma once

#include <hazedumper/plugin-sdk/module_loader.hpp>

namespace hazedumper::impl {
NODISCARD
auto
make_module_loader() noexcept -> module_loader_ptr;
}
