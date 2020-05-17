
#ifndef VTKVIEWSGEOVIS_EXPORT_H
#define VTKVIEWSGEOVIS_EXPORT_H

#ifdef VTKVIEWSGEOVIS_STATIC_DEFINE
#  define VTKVIEWSGEOVIS_EXPORT
#  define VTKVIEWSGEOVIS_NO_EXPORT
#else
#  ifndef VTKVIEWSGEOVIS_EXPORT
#    ifdef vtkViewsGeovis_EXPORTS
        /* We are building this library */
#      define VTKVIEWSGEOVIS_EXPORT __attribute__((visibility("default")))
#    else
        /* We are using this library */
#      define VTKVIEWSGEOVIS_EXPORT __attribute__((visibility("default")))
#    endif
#  endif

#  ifndef VTKVIEWSGEOVIS_NO_EXPORT
#    define VTKVIEWSGEOVIS_NO_EXPORT __attribute__((visibility("hidden")))
#  endif
#endif

#ifndef VTKVIEWSGEOVIS_DEPRECATED
#  define VTKVIEWSGEOVIS_DEPRECATED __attribute__ ((__deprecated__))
#  define VTKVIEWSGEOVIS_DEPRECATED_EXPORT VTKVIEWSGEOVIS_EXPORT __attribute__ ((__deprecated__))
#  define VTKVIEWSGEOVIS_DEPRECATED_NO_EXPORT VTKVIEWSGEOVIS_NO_EXPORT __attribute__ ((__deprecated__))
#endif

#define DEFINE_NO_DEPRECATED 0
#if DEFINE_NO_DEPRECATED
# define VTKVIEWSGEOVIS_NO_DEPRECATED
#endif

/* AutoInit dependencies.  */
#include "vtkViewsInfovisModule.h"

#endif
