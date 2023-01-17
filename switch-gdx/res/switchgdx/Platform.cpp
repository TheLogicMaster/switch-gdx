#include "Clearwing.hpp"

#ifdef __SWITCH__
#include <switch.h>
#endif

std::string vm::getOSLanguage() {
#ifdef __SWITCH__
    u64 languageCode;
    setGetSystemLanguage(&languageCode);
    return (char *)&languageCode;
#else
    return "en-US";
#endif
}

std::string vm::getSystemProperty(const std::string &key) {
#if defined(__SWITCH__)
    if (key == "os.name")
        return "horizon";
    if (key == "os.arch")
        return "aarch64";
#elif defined(__WINRT__)
    if (key == "os.name")
        return "uwp";
    if (key == "os.arch")
        return "x86_64";
#else
    if (key == "os.name")
        return "unknown";
    if (key == "os.arch")
        return "x86_64";
#endif
    if (key == "line.separator")
        return "\n";
    return "";
}
