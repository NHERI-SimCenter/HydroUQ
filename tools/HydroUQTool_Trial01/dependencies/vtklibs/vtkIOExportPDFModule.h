
#ifndef VTKIOEXPORTPDF_EXPORT_H
#define VTKIOEXPORTPDF_EXPORT_H

#ifdef VTKIOEXPORTPDF_STATIC_DEFINE
#  define VTKIOEXPORTPDF_EXPORT
#  define VTKIOEXPORTPDF_NO_EXPORT
#else
#  ifndef VTKIOEXPORTPDF_EXPORT
#    ifdef vtkIOExportPDF_EXPORTS
        /* We are building this library */
#      define VTKIOEXPORTPDF_EXPORT __attribute__((visibility("default")))
#    else
        /* We are using this library */
#      define VTKIOEXPORTPDF_EXPORT __attribute__((visibility("default")))
#    endif
#  endif

#  ifndef VTKIOEXPORTPDF_NO_EXPORT
#    define VTKIOEXPORTPDF_NO_EXPORT __attribute__((visibility("hidden")))
#  endif
#endif

#ifndef VTKIOEXPORTPDF_DEPRECATED
#  define VTKIOEXPORTPDF_DEPRECATED __attribute__ ((__deprecated__))
#  define VTKIOEXPORTPDF_DEPRECATED_EXPORT VTKIOEXPORTPDF_EXPORT __attribute__ ((__deprecated__))
#  define VTKIOEXPORTPDF_DEPRECATED_NO_EXPORT VTKIOEXPORTPDF_NO_EXPORT __attribute__ ((__deprecated__))
#endif

#define DEFINE_NO_DEPRECATED 0
#if DEFINE_NO_DEPRECATED
# define VTKIOEXPORTPDF_NO_DEPRECATED
#endif

/* AutoInit dependencies.  */
#include "vtkIOExportModule.h"
#include "vtkIOExportModule.h"

/* AutoInit implementations.  */
#if defined(vtkIOExportPDF_INCLUDE)
# include vtkIOExportPDF_INCLUDE
#endif
#if defined(vtkIOExportPDF_AUTOINIT)
# include "vtkAutoInit.h"
VTK_AUTOINIT(vtkIOExportPDF)
#endif

#endif
