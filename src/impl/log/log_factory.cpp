#include "log_factory.hpp"

#if defined(HAZEDUMPER_MSVC)
#   include "log_msvc.hpp"
#else
#   include "log_unix.hpp"
#endif

using namespace hazed;

auto
impl::log_factory::create(
    const std::string_view name
) -> log_ptr
{
    const auto hash{ hash_string(name) };

    if (!logs_.contains(hash)) {
        logs_.insert(
            std::make_pair(
                hash,
#if defined(HAZEDUMPER_MSVC)
                std::make_shared<log_msvc>(name)
#else
                std::make_shared<log_unix>(name)
#endif
            )
        );

        logs_[hash]
            ->debug(state_.debug)
            ->verbose(state_.verbose)
            ->info(state_.info)
            ->notice(state_.notice)
        ;
    }

    return logs_[hash];
}

auto
impl::log_factory::debug(
    const bool active
) noexcept -> log_factory*
{
    state_.debug = active;

    for (const auto& [_, ptr] : logs_) {
        ptr->debug(active);
    }

    return this;
}

auto
impl::log_factory::verbose(
    const bool active
) noexcept -> log_factory*
{
    state_.verbose = active;

    for (const auto& [_, ptr] : logs_) {
        ptr->verbose(active);
    }

    return this;
}

auto
impl::log_factory::info(
    const bool active
) noexcept -> log_factory*
{
    state_.info = active;

    for (const auto& [_, ptr] : logs_) {
        ptr->info(active);
    }

    return this;
}

auto
impl::log_factory::notice(
    const bool active
) noexcept -> log_factory*
{
    state_.notice = active;

    for (const auto&[_, ptr] : logs_) {
        ptr->notice(active);
    }

    return this;
}
