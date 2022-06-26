#pragma once

#include "prerequisites.hpp"

namespace hazedumper {
ABSTRACT_CLASS(plugin)
{
public:
    using create_plugin_fn = void(*)(plugin_ptr&);

    virtual
    ~plugin() = default;

    NODISCARD
    virtual
    auto
    name() const noexcept -> std::string_view = 0;

    NODISCARD
    virtual
    auto
    author() const noexcept -> std::string_view = 0;

    NODISCARD
    virtual
    auto
    description() const noexcept -> std::string_view = 0;

    NODISCARD
    virtual
    auto
    priority() const noexcept -> i32 = 0;

    NODISCARD
    virtual
    auto
    load() -> bool = 0;

    NODISCARD
    virtual
    auto
    unload() -> void = 0;

    NODISCARD
    virtual
    auto
    plugin_data() const noexcept -> ptr
    {
        return nullptr;
    }

    NODISCARD
    virtual
    auto
    update_dependencies(
        const dependencies_ptr& deps
    ) -> void
    {}
};
}

#if !defined(HAZEDUMPER_PLUGIN)
#   define HAZEDUMPER_PLUGIN(PluginClass, ...)                \
        extern "C"                                            \
        HAZEDUMPER_EXPORT                                     \
        auto                                                  \
        create_plugin(hazed::plugin_ptr& out) -> void         \
        {                                                     \
            out = std::make_shared<PluginClass>(__VA_ARGS__); \
        }
#endif //HAZEDUMPER_PLUGIN
