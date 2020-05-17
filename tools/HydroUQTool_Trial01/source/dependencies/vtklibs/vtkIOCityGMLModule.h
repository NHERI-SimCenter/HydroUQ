
#ifndef VTKIOCITYGML_EXPORT_H
#define VTKIOCITYGML_EXPORT_H

#ifdef VTKIOCITYGML_STATIC_DEFINE
#  define VTKIOCITYGML_EXPORT
#  define VTKIOCITYGML_NO_EXPORT
#else
#  ifndef VTKIOCITYGML_EXPORT
#    ifdef vtkIOCityGML_EXPORTS
        /* We are building this library */
#      define VTKIOCITYGML_EXPORT __attribute__((visibility("default")))
#    else
        /* We are using this library */
#      define VTKIOCITYGML_EXPORT __attribute__((visibility("default")))
#    endif
#  endif

#  ifndef VTKIOCITYGML_NO_EXPORT
#    define VTKIOCITYGML_NO_EXPORT __attribute__((visibility("hidden")))
#  endif
#endif

#ifndef VTKIOCITYGML_DEPRECATED
#  define VTKIOCITYGML_DEPRECATED __attribute__ ((__deprecated__))
#  define VTKIOCITYGML_DEPRECATED_EXPORT VTKIOCITYGML_EXPORT __attribute__ ((__deprecated__))
#  define VTKIOCITYGML_DEPRECATED_NO_EXPORT VTKIOCITYGML_NO_EXPORT __attribute__ ((__deprecated__))
#endif

#define DEFINE_NO_DEPRECATED 0
#if DEFINE_NO_DEPRECATED
# define VTKIOCITYGML_NO_DEPRECATED
#endif

/* AutoInit dependencies.  */
#include "vtkFiltersGeneralModule.h"
#include "vtkFiltersModelingModule.h"

#endif
