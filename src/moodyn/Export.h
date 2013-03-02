#ifndef MOODYN_EXPORT_H
#define MOODYN_EXPORT_H


#if defined(WIN32) || defined(_MSC_VER) || defined(__CYGWIN__) || defined(__MINGW32__) || defined(__BCPLUSPLUS__) || defined(__MWERKS__)
    #ifdef MOODYN_LIBRARY
      #define MOODYN_EXPORT __declspec(dllexport)
    #else
      #define MOODYN_EXPORT __declspec(dllimport)
    #endif
#else
    #define MOODYN_EXPORT
#endif

#ifndef NULL
  #define NULL 0
#endif

#endif
