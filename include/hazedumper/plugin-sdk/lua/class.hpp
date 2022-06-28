#pragma once

#include <hazedumper/plugin-sdk/prerequisites.hpp>

namespace hazedumper::lua {
FINAL_CLASS(cclass)
{
    friend gateway;
    using callback_fn = i32(*)(const gateway*);

    struct method_info
    {
        std::string name;
        callback_fn fn;

        method_info(
            std::string       name,
            const callback_fn fn
        ) noexcept
            : name(std::move(name))
            , fn(fn)
        {}
    };

    using vec_methods = std::vector<method_info>;

public:
    explicit
    cclass(
        const std::string_view global_name,
        const std::string_view metatable = {}
    ) noexcept
        : global_name_(global_name)
        , metatable_(metatable)
    {
        if (metatable_.empty()) {
            metatable_ = "lua_C";
            metatable_.append(global_name);
        }
    }

    auto
    bind(
        std::string        name,
        const callback_fn  fn
    ) -> cclass&
    {
        if (fn && !name.empty()) {
            methods_.emplace_back(
                std::move(name),
                fn
            );
        }

        return *this;
    }

private:
    std::string global_name_;
    std::string metatable_;
    vec_methods methods_{};
};
}
