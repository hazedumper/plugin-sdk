#pragma once

#include "plugin.hpp"

namespace hazedumper {
FINAL_CLASS(dependencies)
    : public std::enable_shared_from_this<dependencies>
{
    struct plugin_info
    {
        ptr        handle{};
        plugin_ptr ptr{};
    };

    using map_plugins      = std::map<szt, plugin_info>;
    using unload_plugin_fn = std::function<void(ptr)>;

public:
    dependencies(
        module_loader_ptr modules,
        log_factory_ptr   logs
    ) noexcept
        : modules_(std::move(modules))
        , logs_(std::move(logs))
    {}

    NODISCARD
    auto
    process() const noexcept -> process_ptr
    {
        return process_;
    }

    NODISCARD
    auto
    modules() const noexcept -> module_loader_ptr
    {
        return modules_;
    }

    NODISCARD
    auto
    logs() const noexcept -> log_factory_ptr
    {
        return logs_;
    }

    NODISCARD
    auto
    process(
        process_ptr ptr
    ) noexcept -> void
    {
        process_ = std::move(ptr);
    }

    NODISCARD
    auto
    find_plugin(
        const std::string_view name
    ) const noexcept -> plugin_ptr
    {
        const auto hash{ hash_string(name) };

        return plugins_.contains(hash)
            ? plugins_.at(hash).ptr
            : nullptr;
    }

    auto
    insert_plugin(
        ptr const  handle,
        plugin_ptr plugin
    ) -> void
    {
        const auto hash{ hash_string(plugin->name()) };

        if (!plugins_.contains(hash)) {
            plugins_.insert(
                std::make_pair(
                    hash, 
                    plugin_info{
                        handle,
                        std::move(plugin)
                    }
                )
            );
        }
    }

    auto
    shutdown(
        const unload_plugin_fn& callback
    ) noexcept -> void
    {
        process_.reset();

        for (auto& [_, value] : plugins_) {
            auto& [handle, ptr] = value;

            if (callback) {
                callback(handle);
            }

            ptr.reset();
        }

        plugins_.clear();
        modules_.reset();
        logs_.reset();
    }

private:
    module_loader_ptr modules_;
    process_ptr       process_{};
    log_factory_ptr   logs_{};
    map_plugins       plugins_{};
};
}
