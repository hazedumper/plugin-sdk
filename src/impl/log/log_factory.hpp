#pragma once

#include <hazedumper/plugin-sdk/log_factory.hpp>

namespace hazedumper::impl {
FINAL_CLASS(log_factory)
    : public hazed::log_factory
{
    using map_logs = std::map<szt, log_ptr>;

public:
    NODISCARD
    auto
    create(
        std::string_view name
    ) -> log_ptr override;

    auto
    debug(
        bool active
    ) noexcept -> log_factory* override;

    auto
    verbose(
        bool active
    ) noexcept -> log_factory* override;

    auto
    info(
        bool active
    ) noexcept -> log_factory* override;

    auto
    notice(
        bool active
    ) noexcept -> log_factory* override;

private:
    map_logs logs_{};

    struct
    {
        bool debug{};
        bool verbose{};
        bool info{};
        bool notice{};
    } state_{};
};
}
