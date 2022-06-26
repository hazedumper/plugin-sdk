#include <hazedumper/fs.hpp>
#include <filesystem>

using namespace hazed;

auto
iterate_directory(
    const std::filesystem::path& path,
    const filesystem::enum_fn&   callback,
    const szt                    max_depth = 1,
    szt                          depth     = 0
) noexcept -> void
{
    if (depth > max_depth) {
        return;
    }

    for (const auto& it : std::filesystem::directory_iterator(path)) {
        if (it.is_directory()) {
            iterate_directory(it, callback, max_depth, ++depth);
        } else if (it.is_regular_file()) {
            callback(it.path().generic_string());
        }
    }
}

filesystem::filesystem()
{
    directories_.root = std::filesystem::current_path()
        .generic_string();

    const auto init_subdirectory = [this](
        const std::string_view sub, 
        std::string&           out
    ) -> void
    {
        out = directories_.root;

        out.append(sub);

        std::filesystem::create_directory(out);
    };

    init_subdirectory("/plugins/", directories_.plugins);
    init_subdirectory("/lua/", directories_.scripts);
}

auto
filesystem::enum_plugins(
    const enum_fn& callback
) const noexcept -> void
{
    iterate_directory(directories_.plugins, callback);
}

auto
filesystem::enum_scripts(
    const enum_fn& callback
) const noexcept -> void
{
    iterate_directory(directories_.scripts, callback);
}
