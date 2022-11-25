#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__) || defined (_WIN64) || defined (_M_ARM) || defined (_M_ARM64)
    #define SYSWIN
#elif __APPLE__
    #include <TargetConditionals.h>
    #define SYSMAC
#elif __ANDROID__
    // Below __linux__ check should be enough to handle Android,
    // but something may be unique to Android.
#elif __linux__
    #define SYSLINUX
#elif __unix__ // all unices not caught above
    #define SYSUNIX
#else
    #define SYSUKE
#endif