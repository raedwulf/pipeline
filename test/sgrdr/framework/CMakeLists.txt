find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(GLUT)

if (GLUT_FOUND)
  #includes
  include_directories(
    "${CMAKE_CURRENT_SOURCE_DIR}/inc"
    "${GLEW_INCLUDE_DIRS}"
    "${GLUT_INCLUDE_DIR}"
  )

  #definitions
  add_definitions(
    "-DDPTSGRDR_EXPORTS"
    "-D_CRT_SECURE_NO_WARNINGS"
  )

  #sources
  set (DPTSGRDR_SOURCES
    src/SgRdrBackend.cpp
  )

  set (DPTSGRDR_HEADERS
    inc/Config.h
  )

  set (DPTSGRDR_PUBLIC_HEADERS
    SgRdrBackend.h
  )

  source_group(headers FILES ${DPTSGRDR_HEADERS})
  source_group(sources FILES ${DPTSGRDR_SOURCES})
  source_group("" FILES ${DPTSGRDR_PUBLIC_HEADERS})

  #target
  add_library( DPTSgRdr SHARED
     ${DPTSGRDR_SOURCES}
     ${DPTSGRDR_HEADERS}
     ${DPTSGRDR_PUBLIC_HEADERS}
  )

  set_target_properties( DPTSgRdr PROPERTIES SUFFIX ".bkd" FOLDER "DPT/SgRdr" )

  target_link_libraries( DPTSgRdr 
    ${GLUT_LIBRARIES}
    DPUtil
    DPTcore
    DPGL
    DPSgCore
    DPSgRdrRiXGL
  )

  add_dependencies( DPTSgRdr
    DPUtil
    DPTcore
    DPTRiX
    RiXCore
    RiXGL
    DPSgRdrRiXGL
  )

  CopyGLUT( DPTSgRdr "${DP_BINARY_PATH}" )
else()
  message("GLUT not found, disabling DPTSgRdr.")
endif()