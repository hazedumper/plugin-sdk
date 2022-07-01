#pragma once

#include <hazedumper/plugin-sdk/lua/call_state.hpp>
#include <hazedumper/plugin-sdk/lua/class.hpp>

namespace hazedumper::lua {
enum class pseudo_index
{
    registry = -10000,
    env      = -10001,
    globals  = -10002,
};

FINAL_CLASS(gateway)
{
    using callback_fn   = cclass::callback_fn;
    using stack_indices = std::initializer_list<i32>;

public:
    NODISCARD
    static
    auto
    instantiate() noexcept -> const gateway*;

    static
    auto
    destroy(
        const gateway* data
    ) noexcept -> const gateway*;

    NODISCARD
    auto
    exec(
        std::string_view abs_path
    ) const noexcept -> bool;
    
    NODISCARD
    auto
    exec(
        std::string_view content,
        i32              num_args,
        i32              num_results = 0,
        i32              error_func = 0
    ) const noexcept -> call_state;

    auto
    bind(
        std::string_view name,
        callback_fn      fn
    ) const noexcept -> void;

    template<typename T>
    auto
    bind(
        const std::string_view name,
        const T                value
    ) const noexcept -> void
    {
        set_global(name);
        push(value);
    }

    auto
    bind(
        cclass& builder
    ) const noexcept -> void;

    auto
    bind(
        cclass* builder
    ) const noexcept -> void;

    auto
    bind(
        const cclass* builder
    ) const noexcept -> void;

    NODISCARD
    auto
    is_bool(
        i32 index
    ) const noexcept -> bool;

    NODISCARD
    auto
    is_bool(
        i32 first_index,
        i32 last_index
    ) const noexcept -> bool;

    NODISCARD
    auto
    is_bool(
        const stack_indices& indices
    ) const noexcept -> bool;

    NODISCARD
    auto
    is_num(
        i32 index
    ) const noexcept -> bool;

    NODISCARD
    auto
    is_num(
        i32 first_index,
        i32 last_index
    ) const noexcept -> bool;

    NODISCARD
    auto
    is_num(
        const stack_indices& indices
    ) const noexcept -> bool;

    NODISCARD
    auto
    is_text(
        i32 index
    ) const noexcept -> bool;

    NODISCARD
    auto
    is_text(
        i32 first_index,
        i32 last_index
    ) const noexcept -> bool;

    NODISCARD
    auto
    is_text(
        const stack_indices& indices
    ) const noexcept -> bool;

    NODISCARD
    auto
    is_userdata(
        i32 index
    ) const noexcept -> bool;

    NODISCARD
    auto
    is_userdata(
        i32 first_index,
        i32 last_index
    ) const noexcept -> bool;

    NODISCARD
    auto
    is_userdata(
        const stack_indices& indices
    ) const noexcept -> bool;

    NODISCARD
    auto
    is_function(
        i32 index
    ) const noexcept -> bool;

    NODISCARD
    auto
    is_function(
        i32 first_index,
        i32 last_index
    ) const noexcept -> bool;

    NODISCARD
    auto
    is_function(
        const stack_indices& indices
    ) const noexcept -> bool;

    NODISCARD
    auto
    is_nil(
        i32 index
    ) const noexcept -> bool;

    NODISCARD
    auto
    is_nil(
        i32 first_index,
        i32 last_index
    ) const noexcept -> bool;

    NODISCARD
    auto
    is_nil(
        const stack_indices& indices
    ) const noexcept -> bool;

    NODISCARD
    auto
    top() const noexcept -> i32;

    NODISCARD
    auto
    top(
        i32 required
    ) const noexcept -> bool;

    NODISCARD
    auto
    top(
        i32 min,
        i32 max
    ) const noexcept -> bool;

    auto
    pop(
        i32 count
    ) const noexcept -> void;

    NODISCARD
    auto
    popr(
        i32 count
    ) const noexcept -> const gateway*;

    auto
    pop_top() const noexcept -> void;

    NODISCARD
    auto
    pop_topr() const noexcept -> const gateway*;

    auto
    get_global(
        std::string_view name
    ) const noexcept -> void;

    NODISCARD
    auto
    get_globalr(
        std::string_view name
    ) const noexcept -> const gateway*;

    auto
    set_global(
        std::string_view name
    ) const noexcept -> void;

    NODISCARD
    auto
    set_globalr(
        std::string_view name
    ) const noexcept -> const gateway*;
    
    auto
    get_metatable(
        std::string_view name
    ) const noexcept -> void;

    auto
    set_metatable(
        i32 index
    ) const noexcept -> void;

    NODISCARD
    auto
    new_userdata(
        szt size
    ) const noexcept -> ptr;

    NODISCARD
    auto
    load_file(
        std::string_view abs_path
    ) const noexcept -> call_state;

    NODISCARD
    auto
    pcall(
        i32 num_args,
        i32 num_results,
        i32 error_func
    ) const noexcept -> call_state;

    auto
    call(
        i32 num_args,
        i32 num_results
    ) const noexcept -> void;

    NODISCARD
    auto
    ref(
        pseudo_index index
    ) const noexcept -> i32;

    auto
    raw_get_index(
        i32 index,
        i32 n
    ) const noexcept -> void;

    auto
    raw_get_index(
        pseudo_index index,
        i32          n
    ) const noexcept -> void;

    NODISCARD
    auto
    raw_get_indexr(
        i32 index,
        i32 n
    ) const noexcept -> const gateway*;

    NODISCARD
    auto
    raw_get_indexr(
        pseudo_index index,
        i32          n
    ) const noexcept -> const gateway*;

    auto
    raw_set_index(
        i32 index,
        i32 n
    ) const noexcept -> void;

    auto
    raw_set_index(
        pseudo_index index,
        i32          n
    ) const noexcept -> void;

    NODISCARD
    auto
    raw_set_indexr(
        i32 idx,
        i32 ref_id
    ) const noexcept -> const gateway*;

    NODISCARD
    auto
    raw_set_indexr(
        pseudo_index idx,
        i32          ref_id
    ) const noexcept -> const gateway*;

    auto
    raw_set(
        i32 index
    ) const noexcept -> void;

    NODISCARD
    auto
    raw_setr(
        i32 index
    ) const noexcept -> const gateway*;

    auto
    raw_get(
        i32 index
    ) const noexcept -> void;

    NODISCARD
    auto
    raw_getr(
        i32 index
    ) const noexcept -> const gateway*;

    NODISCARD
    auto
    table_length(
        i32 index
    ) const noexcept -> szt;

    NODISCARD
    auto
    boolean(
        i32 index,
        bool fallback = false,
        bool cleanup = false
    ) const noexcept -> bool;

    auto
    get_table(
        i32 index
    ) const noexcept -> void;

    NODISCARD
    auto
    get_tabler(
        i32 index
    ) const noexcept -> const gateway*;

    NODISCARD
    auto
    set_table(
        i32 index
    ) const noexcept -> void;

    NODISCARD
    auto
    set_tabler(
        i32 index
    ) const noexcept -> const gateway*;    

    NODISCARD
    auto
    text(
        i32         index,
        std::string fallback = {},
        bool        cleanup = false
    ) const -> std::string;

    template<typename T>
    NODISCARD
    auto
    new_userdata() const noexcept -> T**
    {
        return static_cast<T**>(new_userdata(sizeof(T)));
    }

    template<typename T>
    auto
    destroy_userdata(
        const i32              index,
        const std::string_view name
    ) const noexcept -> void
    {
        if (auto* const ptr{ userdata<T>(index, name) }) {
            delete ptr;
        }
    }

    template<typename T>
    NODISCARD
    auto
    num(
        const i32  index,
        const T    fallback = T{},
        const bool cleanup =  false
    ) const noexcept -> T
    {
        static_assert(
            std::is_integral_v<T>       ||
            std::is_enum_v<T>           ||
            std::is_floating_point_v<T>,
            "Type T must be enum, integral or floating"
        );

        if constexpr (std::is_floating_point_v<T>) {
            static_cast<T>(
                get_number(
                    index,
                    static_cast<f64>(fallback),
                    cleanup
                )
            );
        }

        return static_cast<T>(
            get_integer(
                index,
                static_cast<i64>(fallback),
                cleanup
            )
        );
    }

    template<typename T>
    NODISCARD
    auto
    userdata(
        const i32              index,
        const std::string_view name,
        const bool             cleanup = false
    ) const noexcept -> T*
    {
        auto** const ptr{
            get_userdata(
                index,
                name,
                cleanup
            )
        };

        return ptr
            ? *reinterpret_cast<T**>(ptr)
            : nullptr;
    }

    template<typename T>
    NODISCARD
    auto
    value(
        const i32  index,
        T          fallback = T{},
        const bool cleanup = false
    ) const -> T
    {
        static_assert(
            std::is_same_v<bool, T>        ||
            std::is_floating_point_v<T>    ||
            std::is_integral_v<T>          ||
            std::is_enum_v<T>              ||
            std::is_same_v<std::string, T>,
            "Type T mst be bool, floating"
            ", integral, enum or std::string"
        );

        if constexpr (std::is_same_v<bool, T>) {
            return boolean(index, fallback, cleanup);
        }
        if constexpr (
            std::is_floating_point_v<T> || 
            std::is_integral_v<T>       || 
            std::is_enum_v<T>
        ) {
            return num<T>(index, fallback, cleanup);
        }
        if constexpr (std::is_same_v<std::string, T>) {
            return text(index, std::move(fallback), cleanup);
        }

        return fallback;
    }

    template<typename T>
    auto
    push(
        const T value
    ) const noexcept -> const gateway*
    {
        static_assert(
            std::is_same_v<bool, T>                                   ||
            std::is_floating_point_v<T>                               ||
            std::is_integral_v<T>                                     ||
            std::is_enum_v<T>                                         ||
            std::is_same_v<const char*, T>                            ||
            std::is_null_pointer_v<T>                                 ||
            std::is_same_v<T, std::initializer_list<std::nullptr_t>>  ||
            std::is_same_v<std::string, T>                            ||
            std::is_same_v<std::string_view, T>,
            "Type T must be bool, floating, integral, enum"
            ", const char*, std::string or std::string_view"
        );

        if constexpr (std::is_same_v<bool, T>) {
            push_bool(value);
        }
        if constexpr (std::is_floating_point_v<T>) {
            push_number(static_cast<f64>(value));
        }
        if constexpr (std::is_integral_v<T> || std::is_enum_v<T>) {
            push_integer(static_cast<i64>(value));
        }
        if constexpr (
            std::is_null_pointer_v<T> ||
            std::is_same_v<T, std::initializer_list<std::nullptr_t>>
        ) {
            if constexpr (std::is_same_v<T, std::initializer_list<std::nullptr_t>>) {
                push_nil(value.size());
            }
            push_nil();
        }
        if constexpr (
            std::is_same_v<const char*, T> || 
            std::is_same_v<std::string, T> ||
            std::is_same_v<std::string_view, T>
        ) {
            push_text(value);
        }

        return this;
    }

    template<typename T>
    auto
    push(
        const std::string_view name,
        T* const               userdata
    ) const noexcept -> const gateway*
    {
        if (userdata) {
            if (auto** const init{ new_userdata<T>() }) {
                *init = userdata;

                get_metatable(name);
                set_metatable(-2);
            }
        }
        return this;
    }


    template<i32 ReturnCount>
    NODISCARD
    constexpr
    auto
    ret() const noexcept -> i32
    {
        return ReturnCount;
    }

    NODISCARD
    auto
    ret(
        const i32 count
    ) const noexcept -> i32
    {
        return count;
    }

private:
    NODISCARD
    auto
    get_number(
        i32  index,
        f64  fallback,
        bool cleanup = false
    ) const noexcept -> f64;

    NODISCARD
    auto
    get_integer(
        i32  index,
        i64  fallback,
        bool cleanup = false
    ) const noexcept -> i64;

    NODISCARD
    auto
    get_userdata(
        i32              index,
        std::string_view name,
        bool             cleanup = false
    ) const noexcept -> ptr*;

    auto
    push_bool(
        bool active
    ) const noexcept -> void;

    auto
    push_number(
        f64 value
    ) const noexcept -> void;

    auto
    push_integer(
        i64 value
    ) const noexcept -> void;

    auto
    push_text(
        const char* value
    ) const noexcept -> void;

    auto
    push_text(
        std::string_view value
    ) const noexcept -> void;

    auto
    push_nil(
        szt count = 1
    ) const noexcept -> void;
};
}

#if !defined(HAZEDUMPER_LUA_C_FUNC_DECLARATION)
#   define HAZEDUMPER_LUA_C_FUNC_DECLARATION(Name)    \
        auto                                         \
        lua_##Name(                                  \
            const hazed::lua::gateway* const gateway \
        ) -> hazed::i32
#endif //HAZEDUMPER_LUA_C_FUNC_DECLARATION

#if !defined(HAZEDUMPER_LUA_C_FUNC)
#   define HAZEDUMPER_LUA_C_FUNC(Name)       \
        static                                \
        HAZEDUMPER_LUA_C_FUNC_DECLARATION(Name)
#endif //HAZEDUMPER_LUA_C_FUNC

#if !defined(HAZEDUMPER_LUA_C_LAMBDA)
#   define HAZEDUMPER_LUA_C_LAMBDA() \
        [](const hazed::lua::gateway* const gateway) -> i32
#endif //HAZEDUMPER_LUA_C_LAMBDA
