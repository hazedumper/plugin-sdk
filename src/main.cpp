#include "impl/cli.hpp"
#include "impl/module_loader.hpp"

using namespace hazed;

auto
main(
    const i32          argc,
    const char** const argv
) -> i32
{

    const auto cli{ impl::command_line(argc, argv) };

    if (cli != 0) {
        return cli == -1
            ? EXIT_SUCCESS
            : EXIT_FAILURE;
    }    
    
    const auto deps{ impl::make_dependency_container() };
    const auto modules{ deps->modules() };

    deps->shutdown(
        [&modules](ptr const handle)
        {
            modules->close(handle);
        }
    );

    return 0;
}
