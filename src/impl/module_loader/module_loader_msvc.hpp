#pragma once

#include "abstract_module_loader.hpp"

namespace hazedumper::impl {
FINAL_CLASS(module_loader_msvc)
    : public abstract_module_loader
{
    auto
    close_by_hash(
        szt hash
    ) noexcept -> void;

public:
    module_loader_msvc() noexcept = default;

    ~module_loader_msvc() override;

    auto
    open(
        std::string_view name
    ) -> ptr override;
    
    auto
    close(
        std::string_view name
    ) -> void override;
    
    auto
    close(
        cptr handle
    ) -> void override;

    NODISCARD
    auto
    exported(
        const char*      module_name,
        std::string_view name
    ) const noexcept -> ptr override;

    NODISCARD
    auto
    exported(
        cptr             handle,
        std::string_view name
    ) const noexcept -> ptr override;
};
}
