#include <filesystem>

#ifdef _WIN32
    #include <windows.h>
#else
    #include <unistd.h>
#endif

std::filesystem::path get_executable_path()
{
#ifdef _WIN32
    std::wstring buffer(MAX_PATH, L'\0');

    DWORD size = GetModuleFileNameW(
        nullptr,
        buffer.data(),
        static_cast<DWORD>(buffer.size())
    );

    while (size == buffer.size())
    {
        buffer.resize(buffer.size() * 2);

        size = GetModuleFileNameW(
            nullptr,
            buffer.data(),
            static_cast<DWORD>(buffer.size())
        );
    }

    if (size == 0)
        return {};

    buffer.resize(size);
    return std::filesystem::path(buffer);
#else
    return std::filesystem::read_symlink(
        std::filesystem::path("/proc/self/exe")
    );
#endif
}
