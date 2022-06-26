#pragma once

#include <hazedumper/plugin-sdk/module_loader.hpp>

namespace hazedumper::impl {
ABSTRACT_CLASS(abstract_module_loader)
    : public module_loader
{
    using map_modules = std::map<szt, ptr>;

public:
    NODISCARD
    auto
    exported(
        const std::string_view module_name, 
        const std::string_view name
    ) const noexcept -> ptr override
    {
        return dynamic_cast<const module_loader*>(this)
            ->exported(module_name.data(), name);
    }

protected:
    NODISCARD
    auto
    get_hash_from_handle(
        cptr const handle
    ) const noexcept -> szt
    {
        for (const auto& [key, value] : modules_) {
            if (value == handle) {
                return key;
            }
        }

        return 0;
    }
    
    map_modules modules_{};
};
}
