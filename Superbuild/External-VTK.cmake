#---------------------------------------------------------------------------
# Get and build vtk

if(NOT VTK_TAG)
  set(VTK_TAG "v7.0.0")
endif()

ExternalProject_Add(VTK
  GIT_REPOSITORY "${git_protocol}://vtk.org/VTK.git"
  GIT_TAG "${VTK_TAG}"
  SOURCE_DIR VTK
  BINARY_DIR VTK-build
  CMAKE_GENERATOR ${gen}
  CMAKE_ARGS
    ${ep_common_args}
    ${_wrap_python_args}
    -DBUILD_SHARED_LIBS:BOOL=ON
    -DBUILD_EXAMPLES:BOOL=OFF
    -DBUILD_TESTING:BOOL=OFF
    -DVTK_Group_Web:BOOL=ON
    -DModule_vtkImagingMath:BOOL=ON
    -DVTK_WRAP_PYTHON:BOOL=ON
    -DExternalData_OBJECT_STORES:STRING=${ExternalData_OBJECT_STORES}
    "-DPYTHON_EXECUTABLE:FILEPATH=${PYTHON_EXECUTABLE}"
    "-DPYTHON_INCLUDE_DIR:PATH=${PYTHON_INCLUDE_DIR}"
    "-DPYTHON_LIBRARY:PATH=${PYTHON_LIBRARY}"
    -DVTK_USE_SYSTEM_ZLIB:BOOL=ON
    "-DZLIB_ROOT:PATH=${ZLIB_ROOT}"
    "-DZLIB_INCLUDE_DIR:PATH=${ZLIB_INCLUDE_DIR}"
    "-DZLIB_LIBRARY:FILEPATH=${ZLIB_LIBRARY}"
  INSTALL_COMMAND ""
  LOG_DOWNLOAD 0
  LOG_UPDATE 0
  DEPENDS Python zlib
)

set(VTK_DIR ${CMAKE_BINARY_DIR}/VTK-build)
