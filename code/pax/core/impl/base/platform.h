#ifndef PAX_CORE_BASE_PLATFORM_H
#define PAX_CORE_BASE_PLATFORM_H

#define PAX_WORD_NONE  0
#define PAX_WORD_32    1
#define PAX_WORD_64    2
#define PAX_WORD_COUNT 3

#ifndef PAX_WORD

    #if defined(_WIN64) || defined(__PL64__) || defined(__x86_64__) || defined(__amd64__) || defined(__aarch64__)

        #define PAX_WORD PAX_WORD_64

    #elif defined(_WIN32) || defined(__ILP32__) || defined(_i386_)

        #define PAX_WORD PAX_WORD_32

    #else

        #define PAX_WORD PAX_WORD_NONE

    #endif

#endif

#define PAX_SYSTEM_NONE    0
#define PAX_SYSTEM_WINDOWS 1
#define PAX_SYSTEM_LINUX   2
#define PAX_SYSTEM_MAX     3

#ifndef PAX_SYSTEM

    #if defined(_WIN32) || defined(_WIN64)

        #define PAX_SYSTEM PAX_SYSTEM_WINDOWS

    #elif defined(__linux__)

        #define PAX_SYSTEM PAX_SYSTEM_LINUX

    #else

        #define PAX_SYSTEM PAX_SYSTEM_NONE

    #endif

#endif

#endif // PAX_CORE_BASE_PLATFORM_H
