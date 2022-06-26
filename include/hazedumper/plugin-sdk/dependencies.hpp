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
    using unload_plugin_fn = std::function<void(const plugin_ptr&, ptr)>;

public:
    dependencies() = default;

    NODISCARD
    auto
    process() const noexcept -> process_ptr
    {
        return process_;
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
        const auto hash{
            std::hash<
                std::string_view
            >{}(name)
        };

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
        const auto hash{
            std::hash<
                std::string_view
            >{}(plugin->name())
        };

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
                callback(ptr, handle);
            }

            ptr.reset();
        }

        plugins_.clear();
    }

private:
    process_ptr process_{};
    map_plugins plugins_{};
};
}
