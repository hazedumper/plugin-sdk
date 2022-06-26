#pragma once

#include <hazedumper/plugin-sdk/process.hpp>

FINAL_CLASS(msvc_process)
    : public hazed::process
{
    auto
    internal_detach() noexcept -> void;

    NODISCARD
    auto
    detect_architecture() noexcept -> bool;

    NODISCARD
    constexpr
    auto
    has_valid_handle() const noexcept -> bool
    {
        return handle_ && handle_ != INVALID_HANDLE_VALUE;
    }

public:
    msvc_process() = default;

    ~msvc_process() override;
    
    auto
    attach(
        std::string_view name
    ) -> bool override;
    
    auto
    attach(
        hazed::u32 pid
    ) -> bool override;
    
    auto
    detach() noexcept -> void override;
    
    auto
    get_image(
        std::string_view      name,
        hazed::pattern::cache cache_strategy
    ) -> hazed::image_ptr override;
    
    auto
    read_mem(
        hazed::uptr address,
        hazed::ptr  buffer,
        hazed::szt  size
    ) const noexcept -> void override;
    
    auto
    write_mem(
        hazed::uptr address,
        hazed::cptr buffer,
        hazed::szt  size
    ) const noexcept -> void override;

private:
    hazedumper::ptr handle_{ INVALID_HANDLE_VALUE };
    bool            x86_{ false };
};
