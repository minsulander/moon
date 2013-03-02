#ifndef MOON_EXPORT_H
#define MOON_EXPORT_H


#if defined(WIN32) || defined(_MSC_VER) || defined(__CYGWIN__) || defined(__MINGW32__) || defined(__BCPLUSPLUS__) || defined(__MWERKS__)
    #ifdef MOON_LIBRARY
      #define MOON_EXPORT __declspec(dllexport)
    #else
      #define MOON_EXPORT __declspec(dllimport)
    #endif
	#ifdef MOON_PLUGIN
		#define MOON_PLUGIN_EXPORT __declspec(dllexport)
	#else
		#define MOON_PLUGIN_EXPORT __declspec(dllimport)
	#endif
#else
    #define MOON_EXPORT
	#define MOON_PLUGIN_EXPORT
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
