#include "module_loader_factory.hpp"

#if defined(HAZEDUMPER_MSVC)
#   include "module_loader_msvc.hpp"
#else
#   include "module_loader_unix.hpp"
#endif


namespace hazedumper::impl {
auto
make_module_loader() noexcept -> module_loader_ptr
{
    return std::make_shared<
#if defined(HAZEDUMPER_MSVC)
        module_loader_msvc
#else
        module_loader_unix
#endif
    >();
}
}
