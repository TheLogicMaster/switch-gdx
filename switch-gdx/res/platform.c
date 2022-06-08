#include "cn1_globals.h"
#include <string.h>

#ifdef __SWITCH__
#include <switch.h>
#endif

JAVA_OBJECT getOSLanguage(CODENAME_ONE_THREAD_STATE) {
#ifdef __SWITCH__
    u64 languageCode;
    setGetSystemLanguage(&languageCode);
    return fromNativeString(threadStateData, (char *)&languageCode);
#else
    return fromNativeString(threadStateData, "en-US");
#endif
}

JAVA_OBJECT getSystemProperty(CODENAME_ONE_THREAD_STATE, const char *key) {
#if defined(__SWITCH__)
    if (!strcmp(key, "os.name"))
        return fromNativeString(threadStateData, "horizon");
    if (!strcmp(key, "os.arch"))
        return fromNativeString(threadStateData, "aarch64");
#elif defined(__WINRT__)
    if (!strcmp(key, "os.name"))
        return fromNativeString(threadStateData, "uwp");
    if (!strcmp(key, "os.arch"))
        return fromNativeString(threadStateData, "x86_64");
#else
    if (!strcmp(key, "os.name"))
        return fromNativeString(threadStateData, "unknown");
    if (!strcmp(key, "os.arch"))
        return fromNativeString(threadStateData, "x86_64");
#endif
    if (!strcmp(key, "line.separator"))
        return fromNativeString(threadStateData, "\n");
    return JAVA_NULL;
}
