#ifndef MOONET_EXPORT_H
#define MOONET_EXPORT_H


#if defined(WIN32) || defined(_MSC_VER) || defined(__CYGWIN__) || defined(__MINGW32__) || defined(__BCPLUSPLUS__) || defined(__MWERKS__)
    #ifdef MOONET_LIBRARY
      #define MOONET_EXPORT __declspec(dllexport)
    #else
      #define MOONET_EXPORT __declspec(dllimport)
    #endif
#else
    #define MOONET_EXPORT
#endif

#ifndef NULL
  #define NULL 0
#endif

#endif
