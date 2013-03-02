#ifndef MLOG_EXPORT_H
#define MLOG_EXPORT_H

#if defined(WIN32) || defined(_MSC_VER) || defined(__CYGWIN__) || defined(__MINGW32__) || defined(__BCPLUSPLUS__) || defined(__MWERKS__)
    #ifdef MLOG_LIBRARY
      #define MLOG_EXPORT __declspec(dllexport)
    #else
      #define MLOG_EXPORT __declspec(dllimport)
    #endif
#else
    #define MLOG_EXPORT
#endif

#endif
