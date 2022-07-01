#pragma once

#include "plugin.hpp"

namespace hazedumper {
ABSTRACT_CLASS(dependencies)
{
protected:
    struct plugin_info
    {
        ptr        handle{};
        plugin_ptr ptr{};
    };

    using map_plugins      = std::map<szt, plugin_info>;
    using unload_plugin_fn = std::function<void(ptr)>;

public:
    virtual
    ~dependencies() = default;

    NODISCARD
    virtual
    auto
    process() const noexcept -> process_ptr = 0;

    NODISCARD
    virtual
    auto
    modules() const noexcept -> module_loader_ptr = 0;

    NODISCARD
    virtual
    auto
    logs() const noexcept -> log_factory_ptr = 0;

    NODISCARD
    virtual
    auto
    fs() const noexcept -> filesystem_ptr = 0;

    NODISCARD
    virtual
    auto
    cache() const noexcept -> offset_cache_ptr = 0;

    NODISCARD
    virtual
    auto
    lua() const noexcept -> const lua::gateway* = 0;

    virtual
    auto
    process(
        process_ptr ptr
    ) noexcept -> void = 0;

    NODISCARD
    virtual
    auto
    find_plugin(
        std::string_view name
    ) const noexcept -> plugin_ptr = 0;

    auto
    virtual
    insert_plugin(
        ptr        handle,
        plugin_ptr plugin
    ) -> void = 0;

    auto
    virtual
    add_generator(
        generator_ptr gen
    ) noexcept -> void =  0;

    auto
    virtual
    shutdown(
        HAZEDUMPER_CONST_REF(unload_plugin_fn) callback
    ) noexcept -> void = 0;
};
}
