#pragma once

#include "prerequisites.hpp"

namespace hazedumper {
ABSTRACT_CLASS(module_loader)
{
public:
    virtual 
    ~module_loader() = default;

    virtual
    auto
    open(
        std::string_view name
    ) -> ptr = 0;

    virtual
    auto
    close(
        std::string_view name
    ) -> void = 0;

    virtual
    auto
    close(
        cptr handle
    ) -> void = 0;

    NODISCARD
    virtual
    auto
    exported(
        std::string_view module_name,
        std::string_view name
    ) const noexcept -> ptr = 0;

    NODISCARD
    virtual
    auto
    exported(
        const char*      module_name,
        std::string_view name
    ) const noexcept -> ptr = 0;

    NODISCARD
    virtual
    auto
    exported(
        cptr             handle,
        std::string_view name
    ) const noexcept -> ptr = 0;

    template<typename T, typename Argument>
    NODISCARD
    auto
    exported(
        const Argument         arg,
        const std::string_view name
    ) const noexcept -> T
    {
        static_assert(
            std::is_same_v<Argument, std::string_view> ||
            std::is_same_v<Argument, std::string> ||
            std::is_pointer_v<Argument>
        );

        if constexpr (std::is_same_v<Argument, char*>) {
            reinterpret_cast<T>(exported(std::string_view{ arg }, name));
        }

        return reinterpret_cast<T>(exported(arg, name));
    }
};
}
