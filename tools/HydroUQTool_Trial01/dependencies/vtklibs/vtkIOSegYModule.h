
#ifndef VTKIOSEGY_EXPORT_H
#define VTKIOSEGY_EXPORT_H

#ifdef VTKIOSEGY_STATIC_DEFINE
#  define VTKIOSEGY_EXPORT
#  define VTKIOSEGY_NO_EXPORT
#else
#  ifndef VTKIOSEGY_EXPORT
#    ifdef vtkIOSegY_EXPORTS
        /* We are building this library */
#      define VTKIOSEGY_EXPORT __attribute__((visibility("default")))
#    else
        /* We are using this library */
#      define VTKIOSEGY_EXPORT __attribute__((visibility("default")))
#    endif
#  endif

#  ifndef VTKIOSEGY_NO_EXPORT
#    define VTKIOSEGY_NO_EXPORT __attribute__((visibility("hidden")))
#  endif
#endif

#ifndef VTKIOSEGY_DEPRECATED
#  define VTKIOSEGY_DEPRECATED __attribute__ ((__deprecated__))
#  define VTKIOSEGY_DEPRECATED_EXPORT VTKIOSEGY_EXPORT __attribute__ ((__deprecated__))
#  define VTKIOSEGY_DEPRECATED_NO_EXPORT VTKIOSEGY_NO_EXPORT __attribute__ ((__deprecated__))
#endif

#define DEFINE_NO_DEPRECATED 0
#if DEFINE_NO_DEPRECATED
# define VTKIOSEGY_NO_DEPRECATED
#endif

/* AutoInit dependencies.  */
#include "vtkIOImageModule.h"

#endif
