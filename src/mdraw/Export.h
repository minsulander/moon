#ifndef MDRAW_EXPORT_H
#define MDRAW_EXPORT_H


#if defined(WIN32) || defined(_MSC_VER) || defined(__CYGWIN__) || defined(__MINGW32__) || defined(__BCPLUSPLUS__) || defined(__MWERKS__)
    #ifdef MDRAW_LIBRARY
      #define MDRAW_EXPORT __declspec(dllexport)
    #else
      #define MDRAW_EXPORT __declspec(dllimport)
    #endif
#else
    #define MDRAW_EXPORT
#endif

/// \todo move M_PI definition elsewhere
#ifndef M_PI
#define M_PI 3.141592653
#endif
#ifndef M_PIf
#define M_PIf 3.141592653f
#endif

#ifndef NULL
  #define NULL 0
#endif

#endif
