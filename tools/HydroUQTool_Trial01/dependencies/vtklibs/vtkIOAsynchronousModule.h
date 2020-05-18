
#ifndef VTKIOASYNCHRONOUS_EXPORT_H
#define VTKIOASYNCHRONOUS_EXPORT_H

#ifdef VTKIOASYNCHRONOUS_STATIC_DEFINE
#  define VTKIOASYNCHRONOUS_EXPORT
#  define VTKIOASYNCHRONOUS_NO_EXPORT
#else
#  ifndef VTKIOASYNCHRONOUS_EXPORT
#    ifdef vtkIOAsynchronous_EXPORTS
        /* We are building this library */
#      define VTKIOASYNCHRONOUS_EXPORT __attribute__((visibility("default")))
#    else
        /* We are using this library */
#      define VTKIOASYNCHRONOUS_EXPORT __attribute__((visibility("default")))
#    endif
#  endif

#  ifndef VTKIOASYNCHRONOUS_NO_EXPORT
#    define VTKIOASYNCHRONOUS_NO_EXPORT __attribute__((visibility("hidden")))
#  endif
#endif

#ifndef VTKIOASYNCHRONOUS_DEPRECATED
#  define VTKIOASYNCHRONOUS_DEPRECATED __attribute__ ((__deprecated__))
#  define VTKIOASYNCHRONOUS_DEPRECATED_EXPORT VTKIOASYNCHRONOUS_EXPORT __attribute__ ((__deprecated__))
#  define VTKIOASYNCHRONOUS_DEPRECATED_NO_EXPORT VTKIOASYNCHRONOUS_NO_EXPORT __attribute__ ((__deprecated__))
#endif

#define DEFINE_NO_DEPRECATED 0
#if DEFINE_NO_DEPRECATED
# define VTKIOASYNCHRONOUS_NO_DEPRECATED
#endif

/* AutoInit dependencies.  */
#include "vtkIOImageModule.h"

#endif
