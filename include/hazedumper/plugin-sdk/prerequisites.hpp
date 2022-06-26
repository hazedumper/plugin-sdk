#pragma once

#include <cstddef>
#include <cstdint>
#include <string_view>
#include <map>
#include <vector>
#include <functional>

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

namespace hazedumper {
using i8    = std::int8_t;
using i16   = std::int16_t;
using i32   = std::int32_t;
using i64   = std::int64_t;
using iptr  = std::intptr_t;
using u8    = std::uint8_t;
using u16   = std::uint16_t;
using u32   = std::uint32_t;
using u64   = std::uint64_t;
using uptr  = std::uintptr_t;
using szt   = std::size_t;
using ptr   = void*;
using cptr  = const void*;
using raw_t = std::vector<u8>;
using uptrs = std::vector<uptr>;

DECL_SHARED_CLASS(image);
DECL_SHARED_CLASS(process);
DECL_SHARED_CLASS(plugin);
DECL_SHARED_CLASS(dependencies);
}

namespace hazed = hazedumper;
