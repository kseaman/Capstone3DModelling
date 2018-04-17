cmake_minimum_required(VERSION 2.8)

PROJECT(VSVTK)

set(SOURCE_FILES
    VSVTK.cxx
    VTK.cpp
    VTK.h
    PointSelection.h
    PointSelection.cpp
    Align.cpp
    Align.h
	PointStorage.h
	PointStorage.cpp
	Point.h
	Point.cpp
    HeatMap.cpp
    HeatMap.h)

	set(WIN_RESOURCE_FILE mainlogo.rc)


find_package(VTK REQUIRED)
include(${VTK_USE_FILE})

add_executable(VSVTK ${SOURCE_FILES} VSVTK.cxx ${WIN_RESOURCE_FILE})

if(VTK_LIBRARIES)
    target_link_libraries(VSVTK ${VTK_LIBRARIES})
else()
    target_link_libraries(VSVTK vtkHybrid vtkWidgets)
endif()