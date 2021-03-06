#pragma once

#include "prerequisites.hpp"

namespace hazedumper::detail {
ABSTRACT_CLASS(abstract_plugin)
{
public:
    using create_plugin_fn = void(*)(plugin_ptr&);

    virtual
    ~abstract_plugin() = default;

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
    version() const noexcept -> const detail::version& = 0;

    NODISCARD
    virtual
    auto
    target_process() const noexcept -> std::string_view
    {
        return {};
    }

    virtual
    auto
    extend_cli(
        ptr options
    ) const -> void
    {}

    NODISCARD
    virtual
    auto
    pre_load(
        ptr parsed_opptions
    ) -> bool
    {
        return true;
    }

    NODISCARD
    virtual
    auto
    load() -> bool
    {
        return true;
    }

    NODISCARD
    virtual
    auto
    post_load() -> bool
    {
        return true;
    }

    NODISCARD
    virtual
    auto
    unload() -> void
    {}

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

    NODISCARD
    virtual
    auto
    sdk_version() const noexcept -> detail::version
    {
        return hazed::sdk_version;
    }

    NODISCARD
    virtual
    auto
    lua_scripts() const -> strings
    {
        return {};
    }
};
}

namespace hazedumper {
ABSTRACT_CLASS(plugin)
    : public detail::abstract_plugin
{
public:
    explicit
    plugin(
        const detail::version& vers
    ) noexcept
        : version_(vers)
    {}

    plugin(
        const u32 major,
        const u32 minor,
        const u32 patch
    ) noexcept
        : version_(major, minor, patch)
    {}

    NODISCARD
    auto
    version() const noexcept -> const detail::version& override
    {
        return version_;
    }

protected:
    detail::version version_;
};
} //namespace hazedumper

#if !defined(HAZEDUMPER_PLUGIN)
#   define HAZEDUMPER_PLUGIN(PluginClass, ...)                 \
        extern "C"                                             \
        HAZEDUMPER_EXPORT                                      \
        auto                                                   \
        create_plugin(hazed::plugin_ptr& out) -> void          \
        {                                                      \
            static_assert(                                     \
                std::is_base_of_v<hazed::plugin, PluginClass>, \
                MACRO_CONCAT("[hazedumper] class ",            \
                    MACRO_CONCAT(                              \
                        #PluginClass,                          \
                        " doesn't implement hazed::plugin"     \
                    )                                          \
                )                                              \
            );                                                 \
            out = std::make_shared<PluginClass>(__VA_ARGS__);  \
        }
#endif //HAZEDUMPER_PLUGIN
