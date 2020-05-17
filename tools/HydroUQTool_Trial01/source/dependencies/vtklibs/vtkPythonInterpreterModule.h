
#ifndef VTKPYTHONINTERPRETER_EXPORT_H
#define VTKPYTHONINTERPRETER_EXPORT_H

#ifdef VTKPYTHONINTERPRETER_STATIC_DEFINE
#  define VTKPYTHONINTERPRETER_EXPORT
#  define VTKPYTHONINTERPRETER_NO_EXPORT
#else
#  ifndef VTKPYTHONINTERPRETER_EXPORT
#    ifdef vtkPythonInterpreter_EXPORTS
        /* We are building this library */
#      define VTKPYTHONINTERPRETER_EXPORT __attribute__((visibility("default")))
#    else
        /* We are using this library */
#      define VTKPYTHONINTERPRETER_EXPORT __attribute__((visibility("default")))
#    endif
#  endif

#  ifndef VTKPYTHONINTERPRETER_NO_EXPORT
#    define VTKPYTHONINTERPRETER_NO_EXPORT __attribute__((visibility("hidden")))
#  endif
#endif

#ifndef VTKPYTHONINTERPRETER_DEPRECATED
#  define VTKPYTHONINTERPRETER_DEPRECATED __attribute__ ((__deprecated__))
#  define VTKPYTHONINTERPRETER_DEPRECATED_EXPORT VTKPYTHONINTERPRETER_EXPORT __attribute__ ((__deprecated__))
#  define VTKPYTHONINTERPRETER_DEPRECATED_NO_EXPORT VTKPYTHONINTERPRETER_NO_EXPORT __attribute__ ((__deprecated__))
#endif

#define DEFINE_NO_DEPRECATED 0
#if DEFINE_NO_DEPRECATED
# define VTKPYTHONINTERPRETER_NO_DEPRECATED
#endif



#endif
