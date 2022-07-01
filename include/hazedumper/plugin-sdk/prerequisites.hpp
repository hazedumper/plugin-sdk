#pragma once

#if defined(_MSC_VER)
#   if !defined(HAZEDUMPER_MSVC)
#       define HAZEDUMPER_MSVC
#   endif //HAZEDUMPER_MSVC
#elif defined(__APPLE__)
#   include <TargetConditionals.h>
#   if !defined(TARGET_OS_MAC)
#       error "Requires Apple macOS platform"
#   endif //TARGET_OS_MAC
#   if !defined(HAZEDUMPER_MACOS)
#       define HAZEDUMPER_MACOS
#   endif //HAZEDUMPER_MACOS
#elif defined(__linux__) || defined(__unix__)
#   if !defined(HAZEDUMPER_LINUX)
#       define HAZEDUMPER_LINUX
#   endif //HAZEDUMPER_LINUX
#else
#   error "Unknown compiler"
#endif

#if defined(HAZEDUMPER_MSVC)
#   if !defined(NOMINMAX)
#       define NOMINMAX
#   endif //NOMINMAX
#if !defined(WIN32_LEAN_AND_MEAN)
#       define WIN32_LEAN_AND_MEAN
#   endif //WIN32_LEAN_AND_MEAN
#   include <Windows.h>
#endif

#include <cstddef>
#include <cstdint>
#include <functional>
#include <map>
#include <memory>
#include <ranges>
#include <string_view>
#include <vector>

#if defined(HAZEDUMPER_MSVC)
#   if defined(_WIN64)
#       if !defined(HAZEDUMPER_X64)
#           define HAZEDUMPER_X64
#       endif //HAZEDUMPER_X64
#   else
#       if !defined(HAZEDUMPER_X86)
#           define HAZEDUMPER_X86
#       endif //HAZEDUMPER_X86
#   endif
#elif INTPTR_MAX == INT64_MAX
#   if !defined(HAZEDUMPER_X64)
#       define HAZEDUMPER_X64
#   endif //HAZEDUMPER_X64
#else
#   if !defined(HAZEDUMPER_X86)
#       define HAZEDUMPER_X86
#   endif //HAZEDUMPER_X86
#endif

#if !defined(NODISCARD)
#   if __cplusplus >= 201703L
#       define NODISCARD [[nodiscard]]
#   elif defined(_MSC_VER)
#       define NODISCARD _NODISCARD
#   else
#       define NODISCARD [[nodiscard]]
#   endif
#endif //NODISCARD

#if !defined(ABSTRACT)
#   if !defined(_WIN32)
#       define ABSTRACT
#   else
#       define ABSTRACT abstract
#   endif
#endif

#if !defined(ABSTRACT_CLASS)
#   if defined(_WIN32)
#       define ABSTRACT_CLASS(Name) class Name abstract
#   else
#       define ABSTRACT_CLASS(Name) class Name
#   endif
#endif //ABSTRACT_CLASS

#if !defined(FINAL_CLASS)
#   define FINAL_CLASS(Name) class Name final
#endif //FINAL_CLASS

#if !defined(DECL_SHARED_CLASS)
#   define DECL_SHARED_CLASS(Name) \
        class Name; \
        using Name##_ptr = std::shared_ptr<Name>
#endif //DECL_SHARED_CLASS

#if !defined(HAZEDUMPER_EXPORT)
#   if defined(_MSC_VER) || defined(_WIN32)
#       define HAZEDUMPER_EXPORT __declspec(dllexport)
#   elif defined(__GNUC__)
#       define HAZEDUMPER_EXPORT __attribute__((visibility("default")))
#   else
#       define HAZEDUMPER_EXPORT
#   endif
#endif //HAZEDUMPER_EXPORT

#if !defined(MACRO_CONCAT)
#   if !defined(MACRO_CONCAT_IMPL)
#       define MACRO_CONCAT_IMPL(a, b) \
            a##b
#   endif //MACRO_CONCAT_IMPL
#   define MACRO_CONCAT(a, b) MACRO_CONCAT_IMPL(a, b)
#endif //MACRO_CONCAT

#if !defined(HAZEDUMPER_CONST_REF)
#   if defined(HAZEDUMPER_MSVC)
#       define HAZEDUMPER_CONST_REF(Type) const Type&
#   else
#       define HAZEDUMPER_CONST_REF(Type) Type
#   endif
#endif //HAZEDUMPER_CONST_REF

namespace hazedumper {
using f32     = float;
using f64     = double;
using i8      = std::int8_t;
using i16     = std::int16_t;
using i32     = std::int32_t;
using i64     = std::int64_t;
using iptr    = std::intptr_t;
using u8      = std::uint8_t;
using u16     = std::uint16_t;
using u32     = std::uint32_t;
using u64     = std::uint64_t;
using uptr    = std::uintptr_t;
using szt     = std::size_t;
using ptr     = void*;
using cptr    = const void*;
using raw_t   = std::vector<u8>;
using uptrs   = std::vector<uptr>;
using strings = std::vector<std::string>;
}

#include "detail/version.hpp"

namespace hazedumper {
DECL_SHARED_CLASS(offset_cache);
DECL_SHARED_CLASS(image);
DECL_SHARED_CLASS(process);
DECL_SHARED_CLASS(plugin);
DECL_SHARED_CLASS(filesystem);
DECL_SHARED_CLASS(dependencies);
DECL_SHARED_CLASS(module_loader);
DECL_SHARED_CLASS(log);
DECL_SHARED_CLASS(log_factory);
DECL_SHARED_CLASS(generator);

namespace lua {
class cclass;
class gateway;
} //namespace hazedumper::lua

inline
auto
hash_string(
    const std::string_view input
) noexcept -> szt
{
    return std::hash<std::string_view>{}(input);
}

constexpr inline detail::version sdk_version(0, 1, 6);
}

namespace hazed = hazedumper;

#if !defined(CXX_OPTION_RAW)
#   define CXX_OPTION_RAW(Type, Name, Desc) \
        (Name, Desc, cxxopts::value<Type>())
#endif //CXX_OPTION_RAW

#if !defined(CXX_OPTION_RAW_DEFAULT)
#   define CXX_OPTION_RAW_DEFAULT(Type, Name, Desc, Default) \
        (Name, Desc, cxxopts::value<Type>()->default_value(Default))
#endif //CLI_OPTION_RAW_DEFAULT

#if !defined(HAZEDUMPER_CLI_BOOL)
#   define HAZEDUMPER_CLI_BOOL(Name, Desc, Default) \
        CXX_OPTION_RAW_DEFAULT(bool, Name, Desc, #Default)
#endif //HAZEDUMPER_CLI_BOOL

#if !defined(HAZEDUMPER_CLI_INT)
#   define HAZEDUMPER_CLI_INT(Name, Desc) \
        CXX_OPTION_RAW(hazed::i32, Name, Desc)
#endif //HAZEDUMPER_CLI_INT

#if !defined(HAZEDUMPER_CLI_INT_FALLBACK)
#   define HAZEDUMPER_CLI_INT_FALLBACK(Name, Desc) \
        CXX_OPTION_RAW(hazed::i32, Name, Desc)
#endif //HAZEDUMPER_CLI_INT_FALLBACK

#if !defined(HAZEDUMPER_CLI_STRING)
#   define HAZEDUMPER_CLI_STRING(Name, Desc) \
        CXX_OPTION_RAW(std::string, Name, Desc)
#endif //HAZEDUMPER_CLI_STRING

#if !defined(HAZEDUMPER_CLI_STRING_FALLBACK)
#   define HAZEDUMPER_CLI_STRING_DESC(Name, Desc, Default) \
        CXX_OPTION_RAW_DEFAULT(std::string, Name, Desc, Default)
#endif //HAZEDUMPER_CLI_STRING_DESC
