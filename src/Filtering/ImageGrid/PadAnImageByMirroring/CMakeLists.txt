cmake_minimum_required( VERSION 2.8.6 )

project( PadAnImageByMirroring )

find_package( ITK REQUIRED )
include( ${ITK_USE_FILE} )

add_executable( PadAnImageByMirroring Code.cxx )
target_link_libraries( PadAnImageByMirroring ${ITK_LIBRARIES} )

install( TARGETS PadAnImageByMirroring
  DESTINATION bin/ITKExamples/Filtering/ImageGrid
  COMPONENT Runtime
)

install( FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKExamples/Code/Filtering/ImageGrid/PadAnImageByMirroring
  COMPONENT Code
)

enable_testing()
add_test( NAME PadAnImageByMirroringTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/PadAnImageByMirroring
    ${CMAKE_CURRENT_BINARY_DIR}/Gourds.png
    Output.png
)
