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
        ptr handle
    ) -> void = 0;

    NODISCARD
    virtual
    auto
    exported(
        std::string_view name
    ) const noexcept -> ptr = 0;

    NODISCARD
    virtual
    auto
    exported(
        ptr handle
    ) const noexcept -> ptr = 0;

    template<typename T, typename Argument>
    NODISCARD
    auto
    exported(
        const Argument arg
    ) const noexcept -> T
    {
        static_assert(
            std::is_same_v<Argument, std::string_view> ||
            std::is_pointer_v<Argument>
        );

        return reinterpret_cast<T>(exported(arg));
    }
};
}
