# HydroEDP.cmake
# based on HydroEDP.pri by Justin
# Usage:
#   include(path/to/HydroEDP.cmake)
#   simcenter_add_hydro_edp(<target>)

set(EDP_MODULE_DIR "${CMAKE_CURRENT_LIST_DIR}")

function(simcenter_add_hydro_edp target)
  set(dir "${EDP_MODULE_DIR}")
  
  target_include_directories(${target} PRIVATE
    "${dir}/EDP"
  )
  
  set(SOURCES
    "${dir}/EDP/HydroEDP_Selection.cpp"
    "${dir}/EDP/StandardHydroEDP.cpp"
    "${dir}/EDP/StandardTsunamiEDP.cpp"
    "${dir}/EDP/StandardStormSurgeEDP.cpp"
    "${dir}/EDP/StandardWindEDP.cpp"
  )
  
  set(HEADERS
    "${dir}/EDP/HydroEDP_Selection.h"
    "${dir}/EDP/StandardHydroEDP.h"
    "${dir}/EDP/StandardTsunamiEDP.h"
    "${dir}/EDP/StandardStormSurgeEDP.h"
    "${dir}/EDP/StandardWindEDP.h"
  )

  target_sources(${target} PRIVATE ${SOURCES} ${HEADERS})
  
endfunction()