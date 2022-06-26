#include "module_loader_msvc.hpp"

using namespace hazed;
using namespace impl;

auto
module_loader_msvc::close_by_hash(
    const szt hash
) noexcept -> void
{
    if (modules_.contains(hash)) {
        FreeLibrary(static_cast<HMODULE>(modules_[hash]));

        modules_.erase(hash);
    }
}

module_loader_msvc::~module_loader_msvc()
{
    for (const auto& [_, handle] : modules_) {
        FreeLibrary(static_cast<HMODULE>(handle));
    }
}

auto
module_loader_msvc::open(
    const std::string_view name
) -> ptr
{
    const auto hash{ hash_string(name) };

    if (modules_.contains(hash)) {
        return modules_[hash];
    }

    const auto handle{ LoadLibraryA(name.data()) };

    if (handle) {
        modules_.insert(
            std::make_pair(hash, static_cast<ptr>(handle))
        );
    }

    return handle;
}

auto
module_loader_msvc::close(
    const std::string_view name
) -> void
{
    close_by_hash(hash_string(name));
}

auto
module_loader_msvc::close(
    cptr const handle
) -> void
{
    close_by_hash(get_hash_from_handle(handle));
}

auto
module_loader_msvc::exported(
    const char* const      module_name,
    const std::string_view name
) const noexcept -> ptr
{
    const auto hash{ hash_string(module_name) };

    return exported(
        modules_.contains(hash)
            ? modules_.at(hash)
            : GetModuleHandleA(module_name),
        name
    );
}

auto
module_loader_msvc::exported(
    cptr const             handle,
    const std::string_view name
) const noexcept -> ptr
{
    const auto v1 = reinterpret_cast<ptr>(
        GetProcAddress(
            static_cast<HMODULE>(const_cast<ptr>(handle)), 
            name.data()
        )
    );

    return v1;
}
