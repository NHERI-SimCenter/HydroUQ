# HydroRESULTS.cmake
# based on HydroRESULTS.pri by Justin
# Usage:
#   include(path/to/HydroRESULTS.cmake)
#   simcenter_add_hydro_results(<target>)

set(RESULTS_MODULE_DIR "${CMAKE_CURRENT_LIST_DIR}")

function(simcenter_add_hydro_results target)
  set(dir "${RESULTS_MODULE_DIR}")
  
  set(SOURCES
    "${dir}/RESULTS/HydroResults.cpp"
  )

  set(HEADERS
    "${dir}/RESULTS/HydroResults.h"
  )

  target_sources(${target} PRIVATE ${SOURCES} ${HEADERS})
  
endfunction()
