
#ifndef vtkogg_EXPORT_H
#define vtkogg_EXPORT_H

#ifdef VTKOGG_STATIC_DEFINE
#  define vtkogg_EXPORT
#  define VTKOGG_NO_EXPORT
#else
#  ifndef vtkogg_EXPORT
#    ifdef vtkogg_EXPORTS
        /* We are building this library */
#      define vtkogg_EXPORT __attribute__((visibility("default")))
#    else
        /* We are using this library */
#      define vtkogg_EXPORT __attribute__((visibility("default")))
#    endif
#  endif

#  ifndef VTKOGG_NO_EXPORT
#    define VTKOGG_NO_EXPORT __attribute__((visibility("hidden")))
#  endif
#endif

#ifndef VTKOGG_DEPRECATED
#  define VTKOGG_DEPRECATED __attribute__ ((__deprecated__))
#endif

#ifndef VTKOGG_DEPRECATED_EXPORT
#  define VTKOGG_DEPRECATED_EXPORT vtkogg_EXPORT VTKOGG_DEPRECATED
#endif

#ifndef VTKOGG_DEPRECATED_NO_EXPORT
#  define VTKOGG_DEPRECATED_NO_EXPORT VTKOGG_NO_EXPORT VTKOGG_DEPRECATED
#endif

#if 0 /* DEFINE_NO_DEPRECATED */
#  ifndef VTKOGG_NO_DEPRECATED
#    define VTKOGG_NO_DEPRECATED
#  endif
#endif

#endif /* vtkogg_EXPORT_H */
