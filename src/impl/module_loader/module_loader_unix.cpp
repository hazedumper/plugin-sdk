#include "module_loader_unix.hpp"
#include <dlfcn.h>

using namespace hazed;
using namespace impl;

auto
module_loader_unix::close_by_hash(
    const szt hash
) noexcept -> void
{
    if (modules_.contains(hash)) {
        dlclose(modules_[hash]);

        modules_.erase(hash);
    }
}

module_loader_unix::~module_loader_unix()
{
    for (auto& [_, handle] : modules_) {
        dlclose(handle);
    }
}

auto
module_loader_unix::open(
    const std::string_view name
) -> ptr
{
    const auto hash{ hash_string(name) };

    if (modules_.contains(hash)) {
        return modules_[hash];
    }

    const auto handle{ dlopen(name.data(), RTLD_NOW | RTLD_GLOBAL) };

    if (handle) {
        modules_.insert(
            std::make_pair(hash, static_cast<ptr>(handle))
        );
    }

    return handle;
}

auto
module_loader_unix::close(
    const std::string_view name
) -> void
{
    close_by_hash(hash_string(name));
}

auto
module_loader_unix::close(
    cptr const handle
) -> void
{
    close_by_hash(get_hash_from_handle(handle));
}

auto
module_loader_unix::exported(
    const char* const      module_name,
    const std::string_view name
) const noexcept -> ptr
{
    const auto hash{ hash_string(module_name) };

    return exported(
        modules_.contains(hash)
            ? modules_.at(hash)
            : nullptr,
        name
    );
}

auto
module_loader_unix::exported(
    cptr const             handle,
    const std::string_view name
) const noexcept -> ptr
{
    return handle
        ? dlsym(
            const_cast<ptr>(handle),
            name.data()
        ) : nullptr;
}
