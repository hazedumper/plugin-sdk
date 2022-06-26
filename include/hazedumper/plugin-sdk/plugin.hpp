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
    load() -> bool
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

#if !defined(MACRO_CONCAT)
#   if !defined(MACRO_CONCAT_IMPL)
#       define MACRO_CONCAT_IMPL(a, b) \
            a##b
#   endif //MACRO_CONCAT_IMPL
#   define MACRO_CONCAT(a, b) MACRO_CONCAT_IMPL(a, b)
#endif //MACRO_CONCAT

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
