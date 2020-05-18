
#ifndef SQLITE_API_H
#define SQLITE_API_H

#ifdef VTKSQLITE_STATIC_DEFINE
#  define SQLITE_API
#  define VTKSQLITE_NO_EXPORT
#else
#  ifndef SQLITE_API
#    ifdef vtksqlite_EXPORTS
        /* We are building this library */
#      define SQLITE_API __attribute__((visibility("default")))
#    else
        /* We are using this library */
#      define SQLITE_API __attribute__((visibility("default")))
#    endif
#  endif

#  ifndef VTKSQLITE_NO_EXPORT
#    define VTKSQLITE_NO_EXPORT __attribute__((visibility("hidden")))
#  endif
#endif

#ifndef VTKSQLITE_DEPRECATED
#  define VTKSQLITE_DEPRECATED __attribute__ ((__deprecated__))
#endif

#ifndef VTKSQLITE_DEPRECATED_EXPORT
#  define VTKSQLITE_DEPRECATED_EXPORT SQLITE_API VTKSQLITE_DEPRECATED
#endif

#ifndef VTKSQLITE_DEPRECATED_NO_EXPORT
#  define VTKSQLITE_DEPRECATED_NO_EXPORT VTKSQLITE_NO_EXPORT VTKSQLITE_DEPRECATED
#endif

#if 0 /* DEFINE_NO_DEPRECATED */
#  ifndef VTKSQLITE_NO_DEPRECATED
#    define VTKSQLITE_NO_DEPRECATED
#  endif
#endif

#endif /* SQLITE_API_H */
