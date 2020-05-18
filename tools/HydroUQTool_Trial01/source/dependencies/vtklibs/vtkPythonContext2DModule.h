
#ifndef VTKPYTHONCONTEXT2D_EXPORT_H
#define VTKPYTHONCONTEXT2D_EXPORT_H

#ifdef VTKPYTHONCONTEXT2D_STATIC_DEFINE
#  define VTKPYTHONCONTEXT2D_EXPORT
#  define VTKPYTHONCONTEXT2D_NO_EXPORT
#else
#  ifndef VTKPYTHONCONTEXT2D_EXPORT
#    ifdef vtkPythonContext2D_EXPORTS
        /* We are building this library */
#      define VTKPYTHONCONTEXT2D_EXPORT __attribute__((visibility("default")))
#    else
        /* We are using this library */
#      define VTKPYTHONCONTEXT2D_EXPORT __attribute__((visibility("default")))
#    endif
#  endif

#  ifndef VTKPYTHONCONTEXT2D_NO_EXPORT
#    define VTKPYTHONCONTEXT2D_NO_EXPORT __attribute__((visibility("hidden")))
#  endif
#endif

#ifndef VTKPYTHONCONTEXT2D_DEPRECATED
#  define VTKPYTHONCONTEXT2D_DEPRECATED __attribute__ ((__deprecated__))
#  define VTKPYTHONCONTEXT2D_DEPRECATED_EXPORT VTKPYTHONCONTEXT2D_EXPORT __attribute__ ((__deprecated__))
#  define VTKPYTHONCONTEXT2D_DEPRECATED_NO_EXPORT VTKPYTHONCONTEXT2D_NO_EXPORT __attribute__ ((__deprecated__))
#endif

#define DEFINE_NO_DEPRECATED 0
#if DEFINE_NO_DEPRECATED
# define VTKPYTHONCONTEXT2D_NO_DEPRECATED
#endif

/* AutoInit dependencies.  */
#include "vtkRenderingContext2DModule.h"

#endif
