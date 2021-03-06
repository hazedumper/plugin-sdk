#include <hazedumper/plugin-sdk/lua/gateway.hpp>
#include <algorithm>
#include <lua.hpp>

#define LUA_STATE_FROM_GATEWAY() \
    (reinterpret_cast<lua_State*>(const_cast<gateway*>(this)))

using namespace hazed;
using namespace lua;

inline std::map<i32, call_state> lua_call_states{
    { LUA_YIELD,     call_state::yield },
    { LUA_ERRRUN,    call_state::runtime },
    { LUA_ERRSYNTAX, call_state::syntax },
    { LUA_ERRMEM,    call_state::mem_alloc },
    { LUA_ERRERR,    call_state::error },
    { LUA_ERRFILE,   call_state::file },
};

inline
auto
lua_resolve_call_state(
    const i32 state
) noexcept
{
    return lua_call_states.contains(state)
        ? lua_call_states[state]
        : call_state::success;
}

auto
gateway::instantiate() noexcept -> const gateway*
{
    auto* const l{ luaL_newstate() };

    luaL_openlibs(l);

    return reinterpret_cast<const gateway*>(l);
}

auto
gateway::destroy(
    const gateway* const data
) noexcept -> const gateway*
{
    if (data) {
        lua_close(
            reinterpret_cast<lua_State*>(
                const_cast<gateway*>(data)
            )
        );
    }

    return nullptr;
}

auto
gateway::exec(
    const std::string_view abs_path
) const noexcept -> bool
{
    return !luaL_dofile(
        LUA_STATE_FROM_GATEWAY(),
        abs_path.data()
    );
}

auto
gateway::exec(
    const std::string_view content,
    const i32              num_args,
    const i32              num_results,
    const i32              error_func
) const noexcept -> call_state
{
    auto res{ call_state::syntax };

    if (
        !luaL_loadstring(
            LUA_STATE_FROM_GATEWAY(),
            content.data()
        )
    ) {
        res = pcall(
            num_args,
            num_results,
            error_func
        );

        pop(1);
    }

    return res;
}

auto
gateway::bind(
    const std::string_view name,
    const callback_fn      fn
) const noexcept -> void
{
    lua_register(
        LUA_STATE_FROM_GATEWAY(),
        name.data(),
        reinterpret_cast<lua_CFunction>(fn)
    );
}

auto
gateway::bind(
    cclass& builder
) const noexcept -> void
{
    bind(&builder);
}

auto
gateway::bind(
    cclass* const builder
) const noexcept -> void
{
    bind(static_cast<const cclass*>(builder));
}

auto
gateway::bind(
    const cclass* const builder
) const noexcept -> void
{
    auto* const           l{ LUA_STATE_FROM_GATEWAY() };
    std::vector<luaL_Reg> table_data{};

    for (const auto& [name, fn] : builder->methods_) {
        table_data.emplace_back(
            luaL_Reg{
                name.data(),
                reinterpret_cast<lua_CFunction>(fn)
            }
        );
    }

    table_data.emplace_back(luaL_Reg{nullptr, nullptr});

    luaL_newmetatable(l, builder->metatable_.data());

    // for Lua 5.2 and above:
    // luaL_setfuncs(l, table_data.data(), nullptr);
    luaL_register(l, nullptr, table_data.data());
    lua_pushvalue(l, -1);
    lua_setfield(l, -1, "__index");
    lua_setglobal(l, builder->global_name_.data());
}

auto
gateway::is_bool(
    const i32 index
) const noexcept -> bool
{
    return lua_isboolean(LUA_STATE_FROM_GATEWAY(), index);
}

auto
gateway::is_bool(
    const i32 first_index,
    const i32 last_index
) const noexcept -> bool
{
    for (auto i{first_index}; i <= last_index; ++i) {
        if (!is_bool(i)) {
            return false;
        }
    }

    return true;
}

auto
gateway::is_bool(
    const stack_indices& indices
) const noexcept -> bool
{

    return std::ranges::all_of(
        indices.begin(),
        indices.end(),
        [this](const i32 index)
        {
            return is_bool(index);
        }
    );
}

auto
gateway::is_num(
    const i32 index
) const noexcept -> bool
{
    return lua_isnumber(LUA_STATE_FROM_GATEWAY(), index);
}

auto
gateway::is_num(
    const i32 first_index,
    const i32 last_index
) const noexcept -> bool
{
    for (auto i{first_index}; i <= last_index; ++i) {
        if (!is_num(i)) {
            return false;
        }
    }

    return true;
}

auto
gateway::is_num(
    const stack_indices& indices
) const noexcept -> bool
{

    return std::ranges::all_of(
        indices.begin(),
        indices.end(),
        [this](const i32 index)
        {
            return is_num(index);
        }
    );
}

auto
gateway::is_text(
    const i32 index
) const noexcept -> bool
{
    return lua_isstring(LUA_STATE_FROM_GATEWAY(), index);
}

auto
gateway::is_text(
    const i32 first_index,
    const i32 last_index
) const noexcept -> bool
{
    for (auto i{first_index}; i <= last_index; ++i) {
        if (!is_text(i)) {
            return false;
        }
    }

    return true;
}

auto
gateway::is_text(
    const stack_indices& indices
) const noexcept -> bool
{

    return std::ranges::all_of(
        indices.begin(),
        indices.end(),
        [this](const i32 index)
        {
            return is_text(index);
        }
    );
}

auto
gateway::is_userdata(
    const i32 index
) const noexcept -> bool
{
    return lua_isuserdata(LUA_STATE_FROM_GATEWAY(), index);
}

auto
gateway::is_userdata(
    const i32 first_index,
    const i32 last_index
) const noexcept -> bool
{
    for (auto i{first_index}; i <= last_index; ++i) {
        if (!is_userdata(i)) {
            return false;
        }
    }

    return true;
}

auto
gateway::is_userdata(
    const stack_indices& indices
) const noexcept -> bool
{

    return std::ranges::all_of(
        indices.begin(),
        indices.end(),
        [this](const i32 index)
        {
            return is_userdata(index);
        }
    );
}

auto
gateway::is_function(
    const i32 index
) const noexcept -> bool
{
    return lua_isfunction(LUA_STATE_FROM_GATEWAY(), index);
}

auto
gateway::is_function(
    const i32 first_index,
    const i32 last_index
) const noexcept -> bool
{
    for (auto i{first_index}; i <= last_index; ++i) {
        if (!is_function(i)) {
            return false;
        }
    }

    return true;
}

auto
gateway::is_function(
    const stack_indices& indices
) const noexcept -> bool
{

    return std::ranges::all_of(
        indices.begin(),
        indices.end(),
        [this](const i32 index)
        {
            return is_function(index);
        }
    );
}

auto
gateway::is_nil(
    const i32 index
) const noexcept -> bool
{
    return lua_isnil(LUA_STATE_FROM_GATEWAY(), index);
}

auto
gateway::is_nil(
    const i32 first_index,
    const i32 last_index
) const noexcept -> bool
{
    for (auto i{first_index}; i <= last_index; ++i) {
        if (!is_nil(i)) {
            return false;
        }
    }

    return true;
}

auto
gateway::is_nil(
    const stack_indices& indices
) const noexcept -> bool
{

    return std::ranges::all_of(
        indices.begin(),
        indices.end(),
        [this](const i32 index)
        {
            return is_nil(index);
        }
    );
}

auto
gateway::top() const noexcept -> i32
{
    return lua_gettop(LUA_STATE_FROM_GATEWAY());
}

auto
gateway::top(
    const i32 required
) const noexcept -> bool
{
    return top() == required;
}

auto
gateway::top(
    const i32 min,
    const i32 max
) const noexcept -> bool
{
    const auto count{ top() };

    return count >= min && count <= max;
}

auto
gateway::pop(
    const i32 count
) const noexcept -> void
{
    lua_pop(LUA_STATE_FROM_GATEWAY(), count);
}

auto
gateway::popr(
    const i32 count
) const noexcept -> const gateway*
{
    pop(count);

    return this;
}

auto
gateway::pop_top() const noexcept -> void
{
    if (const auto count{ top() }) {
        pop(count);
    }
}

auto
gateway::pop_topr() const noexcept -> const gateway*
{
    pop_top();

    return this;
}

auto
gateway::get_global(
    const std::string_view name
) const noexcept -> void
{
    lua_getglobal(
        LUA_STATE_FROM_GATEWAY(),
        name.data()
    );
}

auto
gateway::get_globalr(
    const std::string_view name
) const noexcept -> const gateway*
{
    get_global(name);

    return this;
}

auto
gateway::set_global(
    const std::string_view name
) const noexcept -> void
{
    lua_setglobal(
        LUA_STATE_FROM_GATEWAY(),
        name.data()
    );
}

auto
gateway::set_globalr(
    const std::string_view name
) const noexcept -> const gateway*
{
    set_global(name);

    return this;
}

auto
gateway::get_metatable(
    const std::string_view name
) const noexcept -> void
{
    luaL_getmetatable(
        LUA_STATE_FROM_GATEWAY(),
        name.data()
    );
}

auto
gateway::set_metatable(
    const i32 index
) const noexcept -> void
{
    lua_setmetatable(
        LUA_STATE_FROM_GATEWAY(),
        index
    );
}

auto
gateway::new_userdata(
    const szt size
) const noexcept -> ptr
{
    return lua_newuserdata(
        LUA_STATE_FROM_GATEWAY(),
        size
    );
}

auto
gateway::load_file(
    const std::string_view abs_path
) const noexcept -> call_state
{
    return lua_resolve_call_state(
        luaL_loadfile(
            LUA_STATE_FROM_GATEWAY(),
            abs_path.data()
        )
    );
}

auto
gateway::pcall(
    const i32 num_args,
    const i32 num_results,
    const i32 error_func
) const noexcept -> call_state
{
    return lua_resolve_call_state(
        lua_pcall(
            LUA_STATE_FROM_GATEWAY(),
            num_args,
            num_results,
            error_func
        )
    );
}

auto
gateway::call(
    const i32 num_args,
    const i32 num_results
) const noexcept -> void
{
    lua_call(
        LUA_STATE_FROM_GATEWAY(),
        num_args,
        num_results
    );
}

auto
gateway::ref(
    const pseudo_index index
) const noexcept -> i32
{
    return luaL_ref(
        LUA_STATE_FROM_GATEWAY(),
        static_cast<
            std::underlying_type_t<pseudo_index>
        >(index)
    );
}

auto
gateway::raw_get_index(
    const i32 index,
    const i32 n
) const noexcept -> void
{
    lua_rawgeti(
        LUA_STATE_FROM_GATEWAY(),
        index,
        n
    );
}

auto
gateway::raw_get_index(
    const pseudo_index index,
    const i32          n
) const noexcept -> void
{
    raw_get_index(
        static_cast<
          std::underlying_type_t<pseudo_index>
        >(index),
        n
    );
}

auto
gateway::raw_get_indexr(
    const i32 index,
    const i32 n
) const noexcept -> const gateway*
{
    raw_get_index(index, n);

    return this;
}

auto
gateway::raw_get_indexr(
    const pseudo_index index,
    const i32          n
) const noexcept -> const gateway*
{
    raw_get_index(index, n);

    return this;
}

auto
gateway::raw_set_index(
    const i32 index,
    const i32 n
) const noexcept -> void
{
    lua_rawseti(
        LUA_STATE_FROM_GATEWAY(),
        index,
        n
    );
}

auto
gateway::raw_set_index(
    const pseudo_index index,
    const i32          n
) const noexcept -> void
{
    raw_set_index(
        static_cast<
            std::underlying_type_t<pseudo_index>
        >(index),
        n
    );
}

auto
gateway::raw_set_indexr(
    const i32 idx,
    const i32 ref_id
) const noexcept -> const gateway*
{
    raw_set_index(idx, ref_id);

    return this;
}

auto
gateway::raw_set_indexr(
    const pseudo_index idx,
    const i32          ref_id
) const noexcept -> const gateway*
{
    raw_set_index(idx, ref_id);

    return this;
}

auto
gateway::raw_set(
    const i32 index
) const noexcept -> void
{
    lua_rawset(
        LUA_STATE_FROM_GATEWAY(),
        index
    );
}

auto
gateway::raw_setr(
    const i32 index
) const noexcept -> const gateway*
{
    raw_set(index);

    return this;
}

auto
gateway::raw_get(
    const i32 index
) const noexcept -> void
{
    lua_rawget(
        LUA_STATE_FROM_GATEWAY(),
        index
    );
}

auto
gateway::raw_getr(
    const i32 index
) const noexcept -> const gateway*
{
    raw_get(index);

    return this;
}

auto
gateway::table_length(
    const i32 index
) const noexcept -> szt
{
    
    return lua_objlen(
        LUA_STATE_FROM_GATEWAY(),
        index
    );
}

auto
gateway::boolean(
    const i32  index,
    const bool fallback,
    const bool cleanup
) const noexcept -> bool
{
    auto res{ fallback };

    if (is_bool(index)) {
        res = !!lua_toboolean(
            LUA_STATE_FROM_GATEWAY(),
            index
        );


        if (cleanup) {
            pop(1);
        }
    }

    return res;
}

auto
gateway::get_table(
    const i32 index
) const noexcept -> void
{
    lua_gettable(
        LUA_STATE_FROM_GATEWAY(),
        index
    );
}

auto
gateway::get_tabler(
    const i32 index
) const noexcept -> const gateway*
{
    get_table(index);

    return this;
}

auto
gateway::set_table(
    const i32 index
) const noexcept -> void
{
    lua_settable(
        LUA_STATE_FROM_GATEWAY(), 
        index
    );
}

auto
gateway::set_tabler(
    const i32 index
) const noexcept -> const gateway*
{
    set_table(index);

    return this;
}

auto
gateway::text(
    const i32   index,
    std::string fallback,
    const bool  cleanup
) const -> std::string
{
    if (is_text(index)) {
        fallback.assign(
            luaL_checkstring(
                LUA_STATE_FROM_GATEWAY(),
                index
            )
        );


        if (cleanup) {
            pop(1);
        }
    }

    return fallback;
}

auto
gateway::get_number(
    const i32  index,
    const f64  fallback,
    const bool cleanup
) const noexcept -> f64
{
    auto res{ fallback };

    if (is_num(index)) {
        res = lua_tonumber(
            LUA_STATE_FROM_GATEWAY(),
            index
        );

        if (cleanup) {
            pop(1);
        }
    }

    return res;
}

auto
gateway::get_integer(
    const i32  index,
    const i64  fallback,
    const bool cleanup
) const noexcept -> i64
{
    auto res{ fallback };

    if (is_num(index)) {
        res = lua_tointeger(
            LUA_STATE_FROM_GATEWAY(),
            index
        );

        if (cleanup) {
            pop(1);
        }
    }

    return res;
}

auto
gateway::get_userdata(
    const i32              index,
    const std::string_view name,
    const bool             cleanup
) const noexcept -> ptr*
{
    ptr res{ nullptr };

    if (!name.empty() && is_userdata(index)) {
        res = luaL_checkudata(
            LUA_STATE_FROM_GATEWAY(),
            index,
            name.data()
        );

        if (cleanup) {
            pop(1);
        }
    }

    return static_cast<ptr*>(res);
}

auto
gateway::push_bool(
    const bool active
) const noexcept -> void
{
    lua_pushboolean(
        LUA_STATE_FROM_GATEWAY(),
        active
    );
}

auto
gateway::push_number(
    const f64 value
) const noexcept -> void
{
    lua_pushnumber(
        LUA_STATE_FROM_GATEWAY(),
        value
    );
}

auto
gateway::push_integer(
    const i64 value
) const noexcept -> void
{
    lua_pushinteger(
        LUA_STATE_FROM_GATEWAY(),
        value
    );
}

auto
gateway::push_text(
    const char* const value
) const noexcept -> void
{
    lua_pushstring(
        LUA_STATE_FROM_GATEWAY(),
        value
    );
}

auto
gateway::push_text(
    const std::string_view value
) const noexcept -> void
{
    push_text(value.data());
}

auto
gateway::push_nil(
    const szt count
) const noexcept -> void
{
    for (szt i{}; i < count; ++i) {
        lua_pushnil(LUA_STATE_FROM_GATEWAY());
    }
}
