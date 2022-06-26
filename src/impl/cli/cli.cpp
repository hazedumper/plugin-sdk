#include "cli.hpp"
#include <cxxopts.hpp>
#include <iostream>

using namespace hazed;

auto
impl::command_line(
    const i32          argc,
    const char** const argv
) -> i32
{
    cxxopts::Options opts("hazedumper", "bla");

    opts.add_options()
        ("c,config",  "", cxxopts::value<std::string>()->default_value("config.yml"))
        ("help", "")
    ;

    const auto result{ opts.parse(argc, argv) };

    if (result.count("help")) {
        std::cout << opts.help() << std::endl;

        return -1;
    }

    return 0;
}
