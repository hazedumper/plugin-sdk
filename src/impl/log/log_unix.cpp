#include "log_unix.hpp"
#include <iomanip>
#include <iostream>
#include <unistd.h>

using namespace hazed;

auto
impl::log_unix::get_color(
    const i32 level
) noexcept -> std::string_view
{
    static std::map<i32, std::string_view> unix_log_level_colors{
        { level_none,  "\x1B[0m" },
        { level_debug,  "\x1B[1;95m" },
        { level_verbose,  "\x1B[1;96m" },
        { level_info,  "\x1B[1;32m" },
        { level_notice,  "\x1B[1;32m" },
        { level_warning,  "\x1B[1;33m" },
        { level_error,  "\x1B[1;31m" },
    };

    return unix_log_level_colors.at(
        unix_log_level_colors.contains(level)
            ? level
            : level_none
    );
}

impl::log_unix::log_unix(
    const std::string_view context
) noexcept
    : abstract_log(context, getpid())
{}

auto
impl::log_unix::handle_message(
    const i32              current_level,
    const std::string_view message
) -> void
{
    char        date_buf[64]{};
    const auto  timestamp{ std::time(nullptr) };
    const auto* now{ std::localtime(&timestamp) };
    const auto  color{ get_color(current_level) };
    const auto  yellow{ get_color(level_warning) };
    const auto  reset{ get_color(-1) };

    std::strftime(
        date_buf,
        sizeof(date_buf),
        "%Y/%m/%d, %X",
        now
    );

    std::cout
        << "["
        << color
        << "hazedumper"
        << reset
        << " - "
        << color
        << process_id_
        << reset
        << "] - "
        << date_buf
        << " - "
        << color
        << level_names_[current_level]
        << reset
        << std::setfill(' ')
        << std::setw(
                    static_cast<std::streamsize>(
                    static_cast<szt>(11) - level_names_[current_level].length()
                )
            )
        << "- ["
        << yellow
        << context_
        << reset
        << "] "
        << color
        << message
        << reset
    ;

    if (new_line_) {
        std::cout << std::endl;
    }
}
