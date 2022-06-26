#include <hazedumper/plugin-sdk/image.hpp>
#include <process.hpp>
#include <TlHelp32.h>

#undef Module32First
#undef Module32Next
#undef MODULEENTRY32
#undef Process32First
#undef Process32Next
#undef PROCESSENTRY32

using namespace hazed;

inline std::map<u16, bool> wow64_architectures = {
    { IMAGE_FILE_MACHINE_IA64,  false },
    { IMAGE_FILE_MACHINE_AMD64, false },
    { IMAGE_FILE_MACHINE_I386,  true },
};

auto
msvc_process::internal_detach() noexcept -> void
{
    if (has_valid_handle()) {
        CloseHandle(handle_);
    }

    handle_ = INVALID_HANDLE_VALUE;
    id_     = 0;
    x86_    = false;
    images_.clear();
}

auto
msvc_process::detect_architecture() noexcept -> bool
{
    u16 process_machine{}, native_machine{};

    if (!IsWow64Process2(handle_, &process_machine, &native_machine)) {
        return false;
    }

    const auto& machine = process_machine == IMAGE_FILE_MACHINE_UNKNOWN
        ? native_machine
        : process_machine;

    const auto success = wow64_architectures.contains(machine);

    if (success) {
        x86_ = wow64_architectures[machine];
    }

    return success;
}

msvc_process::~msvc_process()
{
    internal_detach();
}

auto
msvc_process::attach(
    const std::string_view name
) -> bool
{
    const  std::unique_ptr<void, decltype(&CloseHandle)> snap(
        CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0),
        CloseHandle
    );

    if (snap.get() == INVALID_HANDLE_VALUE) {
        return false;
    }

    auto found = false;
    PROCESSENTRY32 entry{
        .dwSize = sizeof(PROCESSENTRY32)
    };
    
    if (!!Process32First(snap.get(), &entry)) {
        do {
            if (name == entry.szExeFile) {
                found = true;
                break;
            }
        } while (!!Process32Next(snap.get(), &entry));
    }

    return found && attach(entry.th32ProcessID);
}

auto
msvc_process::attach(
    const u32 pid
) -> bool
{
    detach();

    if (!pid) {
        return false;
    }

    handle_ = OpenProcess(PROCESS_ALL_ACCESS, 0, pid);

    if (handle_ == INVALID_HANDLE_VALUE) {
        return false;
    }

    id_ = pid;

    return detect_architecture();
}

auto
msvc_process::detach() noexcept -> void
{
    internal_detach();
}

auto
msvc_process::get_image(
    const std::string_view name,
    const pattern::cache   cache_strategy
) -> image_ptr
{
    const auto hash{ hash_string(name) };

    if (images_.contains(hash)) {
        return images_[hash];
    }

    std::unique_ptr<void, decltype(&CloseHandle)> snap(
        CreateToolhelp32Snapshot(
            TH32CS_SNAPMODULE | (x86_ ? TH32CS_SNAPMODULE32 : 0),
            id_
        ),
        CloseHandle
    );

    if (snap.get() == INVALID_HANDLE_VALUE) {
        return nullptr;
    }

    auto found = false;
    MODULEENTRY32 entry{
        .dwSize = sizeof(MODULEENTRY32)
    };

    if (!!Module32First(snap.get(), &entry)) {
        do {
            if (name == entry.szModule) {
                found = true;
                break;
            }
        } while (!!Module32Next(snap.get(), &entry));
    }

    if (!found) {
        return nullptr;
    }

    images_.insert(
        std::make_pair(
            hash,
            std::make_shared<image>(
                name, 
                reinterpret_cast<uptr>(entry.modBaseAddr), 
                static_cast<szt>(entry.modBaseSize),
                cache_strategy
            )
        )
    );

    return images_[hash];
}

auto
msvc_process::read_mem(
    const uptr address,
    ptr const  buffer,
    const szt  size
) const noexcept -> void
{
    if (handle_ != INVALID_HANDLE_VALUE) {
        szt bytes_read{};

        ReadProcessMemory(
            handle_,
            reinterpret_cast<cptr>(address),
            buffer,
            size,
            &bytes_read
        );
    }
}

auto
msvc_process::write_mem(
    const uptr address,
    cptr const buffer,
    const szt  size
) const noexcept -> void
{
    if (handle_ != INVALID_HANDLE_VALUE) {
        szt bytes_written{};

        WriteProcessMemory(
            handle_,
            reinterpret_cast<ptr>(address),
            buffer,
            size,
            &bytes_written
        );
    }
}
