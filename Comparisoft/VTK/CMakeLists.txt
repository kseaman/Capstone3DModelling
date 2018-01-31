cmake_minimum_required(VERSION 2.8)

PROJECT(VSVTK)

find_package(VTK REQUIRED)
include(${VTK_USE_FILE})

add_executable(VSVTK MACOSX_BUNDLE VSVTK.cxx VTK.h VTK.cpp PointSelection.h PointSelection.cpp Align.h Align.cpp)

if(VTK_LIBRARIES)
    target_link_libraries(VSVTK ${VTK_LIBRARIES})
else()
    target_link_libraries(VSVTK vtkHybrid vtkWidgets)
endif()