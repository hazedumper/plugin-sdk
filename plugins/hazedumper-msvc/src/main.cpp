#include <hazedumper/plugin-sdk/plugin.hpp>
#include <hazedumper/plugin-sdk/dependencies.hpp>
#include <process.hpp>

FINAL_CLASS(hazedumper_msvc)
    : public hazed::plugin
{
public:
    explicit
    hazedumper_msvc(
        const hazed::u32 major,
        const hazed::u32 minor,
        const hazed::u32 patch
    ) noexcept
        : plugin(major, minor, patch)
    {}

    NODISCARD
    auto
    name() const noexcept -> std::string_view override
    {
        return "hazedumper-msvc";
    }

    NODISCARD
    auto
    author() const noexcept -> std::string_view override
    {
        return "Michael K.";
    }

    NODISCARD
    auto
    description() const noexcept -> std::string_view override
    {
        return "Remote process abstraction layer for Windows";
    }

    NODISCARD
    auto
    priority() const noexcept -> hazed::i32 override
    {
        return 20;
    }

    NODISCARD
    auto
    load() -> bool override
    {
        return true;
    }

    NODISCARD
    auto
    unload() -> void override
    {}

    NODISCARD
    auto
    update_dependencies(
        const hazed::dependencies_ptr& deps
    ) -> void override
    {
        deps->process(std::make_shared<msvc_process>());
    }
};

HAZEDUMPER_PLUGIN(hazedumper_msvc, 1, 0, 0);
