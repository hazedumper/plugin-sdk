#include "log_msvc.hpp"
#include <ctime>
#include <iomanip>
#include <iostream>

using namespace hazed;

inline
auto
msvc_console_color(
    const i32 color
) noexcept -> void
{
    SetConsoleTextAttribute(
        GetStdHandle(STD_OUTPUT_HANDLE),
        color != -1
        ? static_cast<u16>(color)
        : static_cast<u16>(FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED)
    );
}

impl::log_msvc::log_msvc(
    const std::string_view context
) noexcept
    : abstract_log(context, GetProcessId(INVALID_HANDLE_VALUE))
{}

auto
impl::log_msvc::handle_message(
    const i32              current_level,
    const std::string_view message
) -> void
{
    char       date_buf[64]{};
    const auto timestamp{ std::time(nullptr) };
    const auto color{ get_color(current_level) };
    tm         now{};

    localtime_s(&now, &timestamp);
    std::strftime(
        date_buf,
        sizeof(date_buf),
        "%Y/%m/%d, %X",
        &now
    );

    std::cout << "[";

    msvc_console_color(color);
    std::cout << "hazedumper";

    msvc_console_color(-1);
    std::cout << " - ";

    msvc_console_color(color);
    std::cout << process_id_;

    msvc_console_color(-1);
    std::cout << "] - " << date_buf << " - ";

    msvc_console_color(color);
    std::cout << level_names_[current_level];

    msvc_console_color(-1);
    std::cout
    << std::setfill(' ')
    << std::setw(
        static_cast<std::streamsize>(
            static_cast<szt>(11) - level_names_[current_level].length()
        )
    ) << "- [";

    msvc_console_color(6);
    std::cout << context_;

    msvc_console_color(-1);
    std::cout << "] ";

    msvc_console_color(color);
    std::cout << message;

    msvc_console_color(-1);

    if (new_line_) {
        std::cout << std::endl;
    }
}
