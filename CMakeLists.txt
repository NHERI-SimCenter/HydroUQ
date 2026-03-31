cmake_minimum_required(VERSION 3.21)

project(Hydro_UQ VERSION 1.0.0 LANGUAGES C CXX)

# ---- C++17 ----
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#
# Qt6
#

find_package(Qt6 REQUIRED COMPONENTS 
    Core Gui Widgets Charts Concurrent Network Sql Qml 
    Quick PrintSupport OpenGL Svg 3DCore 3DRender 3DExtras 3DInput 3DLogic 3DQuick 3DQuickExtras 
    WebEngineWidgets WebEngineCore Core5Compat
)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

#
# Conan Packages
#

find_package(jansson REQUIRED)
find_package(CURL REQUIRED)
find_package(ZLIB REQUIRED)
find_package(Eigen3 REQUIRED)

#
# Source, Headers, Forms and Resources for project
#

set(SOURCES
    main.cpp
    WorkflowAppHydroUQ.cpp
    RunWidget.cpp 
    EVENTS/H20plotwindow.cpp
    SlidingStackedWidget/slidingstackedwidget.cpp
)

set(HEADERS
    WorkflowAppHydroUQ.h
    RunWidget.h
    EVENTS/H20plotwindow.h
    SlidingStackedWidget/slidingstackedwidget.h
)
    
set(RESOURCES 
    images.qrc
    resources.qrc
    objects.qrc
    styles.qrc
    EVENTS/CelerisWebGPU/volumetric.qrc
    images.qrc
    resources.qrc
    styles.qrc
    objects.qrc
    scripts.qrc 
)

set(DISTFILES 
    resources/docs/textAboutHydroUQ.html
    GA4.html
)

set(FORMS
    EVENTS/H20plotwindow.ui
)

#
# ---- Define Target and add ----
#

set(TARGET_NAME Hydro_UQ)

add_executable(${TARGET_NAME}
    ${APP_ICON}
    ${RESOURCES}
    ${FORMS}
    ${SOURCES}
    ${HEADERS}
)

target_include_directories(Hydro_UQ PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/EVENTS/StochasticWaveModel/include
)

#
# all the files needs from Common, HydroEVENTS, HydroEDP and HydroResults
#

# Common
include(${CMAKE_CURRENT_LIST_DIR}/../SimCenterCommon/Common/Common.cmake)
simcenter_add_common(${PROJECT_NAME})

# RandomVariables
include(${CMAKE_CURRENT_LIST_DIR}/../SimCenterCommon/RandomVariables/RandomVariables.cmake)
simcenter_add_randomvariables(${PROJECT_NAME})

# InputSheetBM
include(${CMAKE_CURRENT_LIST_DIR}/../SimCenterCommon/InputSheetBM/InputSheet.cmake)
simcenter_add_inputsheet(${PROJECT_NAME})

# Workflow
include(${CMAKE_CURRENT_LIST_DIR}/../SimCenterCommon/Workflow/Workflow.cmake)
simcenter_add_workflow(${PROJECT_NAME})

# Hydro Related .pri files
include(${CMAKE_CURRENT_LIST_DIR}/HydroEVENTS.cmake)
simcenter_add_hydro_events(${PROJECT_NAME})

include(${CMAKE_CURRENT_LIST_DIR}/HydroRESULTS.cmake)
simcenter_add_hydro_results(${PROJECT_NAME})

include(${CMAKE_CURRENT_LIST_DIR}/HydroEDP.cmake)
simcenter_add_hydro_edp(${PROJECT_NAME})

#
# Platform Specific Logic
#

if(WIN32)
    target_compile_definitions(Hydro_UQ PRIVATE CURL_STATICLIB)
    target_link_libraries(Hydro_UQ PRIVATE 
        Advapi32 
        Crypt32 
        Ws2_32 
        User32
    )
    set_target_properties(Hydro_UQ PROPERTIES WIN32_EXECUTABLE TRUE)
    # Icon handling
    set(EXE_ICON "icons/NHERI-HydroUQ-Icon.ico")
    target_sources(Hydro_UQ PRIVATE ${EXE_ICON})

elseif(APPLE)
    target_link_libraries(Hydro_UQ PRIVATE 
        "-framework CoreFoundation"
        "-framework SystemConfiguration"
        "-framework Security"
    )
    set_target_properties(Hydro_UQ PROPERTIES 
        MACOSX_BUNDLE TRUE
        MACOSX_BUNDLE_INFO_PLIST ${CMAKE_CURRENT_SOURCE_DIR}/Info.plist
        MACOSX_BUNDLE_ICON_FILE NHERI-HydroUQ-Icon.icns
    )
    # Add icon to bundle
    set(MACOSX_BUNDLE_ICON_FILE NHERI-HydroUQ-Icon.icns)
    set_source_files_properties(icons/NHERI-HydroUQ-Icon.icns PROPERTIES MACOSX_BUNDLE_LOCATION "Resources")
    target_sources(Hydro_UQ PRIVATE icons/NHERI-HydroUQ-Icon.icns)

else() # Linux / Ubuntu
    target_compile_definitions(Hydro_UQ PRIVATE CURL_STATICLIB)
    target_link_libraries(Hydro_UQ PRIVATE glut GLU GL)
    target_link_directories(Hydro_UQ PRIVATE /usr/local/lib)
endif()

#
# Link Qt and Conan Libraries
#

target_link_libraries(Hydro_UQ PRIVATE 
    Qt6::Core 
    Qt6::Gui 
    Qt6::Widgets 
    Qt6::Charts 
    Qt6::Concurrent 
    Qt6::Network 
    Qt6::Sql 
    Qt6::Qml 
    Qt6::Quick 
    Qt6::PrintSupport 
    Qt6::OpenGL 
    Qt6::Svg 
    Qt6::3DCore 
    Qt6::3DRender 
    Qt6::3DExtras 
    Qt6::3DInput 
    Qt6::3DLogic 
    Qt6::3DQuick 
    Qt6::3DQuickExtras 
    Qt6::WebEngineWidgets 
    Qt6::WebEngineCore 
    Qt6::WebChannel
    Qt6::Core5Compat
    jansson::jansson
    CURL::libcurl
    ZLIB::ZLIB
    Eigen3::Eigen
)
