set(SRC
    parser/preprocessor.cpp
    parser/tokenizer.cpp
    parser/parser.tab.cc
    parser/parser.cpp
    parser/fixedform_tokenizer.cpp

    semantics/ast_symboltable_visitor.cpp
    semantics/ast_body_visitor.cpp
    semantics/ast_to_asr.cpp

    fortran_evaluator.cpp

    pickle.cpp
    ast_serialization.cpp
    cwrapper.cpp

    ast_to_src.cpp
    ast_to_openmp.cpp

    mod_to_asr.cpp

    utils.cpp
  )

  if (WITH_WHEREAMI)
    set(SRC ${SRC} ../bin/tpl/whereami/whereami.cpp)
  endif()

  if (WITH_XEUS)
    set(SRC ${SRC}
      fortran_kernel.cpp
    )
  endif()
  if (WITH_JSON)
    set(SRC ${SRC}
      ast_to_json.cpp
    )
endif()
add_library(lfortran_lib STATIC ${SRC})
target_include_directories(lfortran_lib PRIVATE $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>)

configure_file(config.h.cmakein config.h @ONLY)
target_link_libraries(lfortran_lib asr lfortran_runtime_static)


if (WITH_ZLIB)
    target_link_libraries(lfortran_lib ZLIB::ZLIB)
endif()

target_include_directories(lfortran_lib BEFORE PUBLIC ${lfortran_SOURCE_DIR}/src)
target_include_directories(lfortran_lib BEFORE PUBLIC ${lfortran_BINARY_DIR}/src)
if (WITH_LIBUNWIND)
    target_link_libraries(lfortran_lib p::libunwind)
endif()
if (WITH_XEUS)
    target_link_libraries(lfortran_lib xeus xeus-zmq)
endif()
if (WITH_JSON)
    target_link_libraries(lfortran_lib p::rapidjson)
endif()
if (WITH_BFD)
    target_link_libraries(lfortran_lib p::bfd)
endif()
if (WITH_LINK)
    target_link_libraries(lfortran_lib p::link)
endif()
if (WITH_EXECINFO)
    target_link_libraries(lfortran_lib p::execinfo)
endif()
if (WITH_LLVM)
    if (WITH_MLIR)
        target_link_libraries(lfortran_lib p::mlir)
    endif()
    target_link_libraries(lfortran_lib p::llvm)
endif()
#install(TARGETS lfortran_lib
#    RUNTIME DESTINATION bin
#    ARCHIVE DESTINATION lib
#    LIBRARY DESTINATION lib
#)

add_subdirectory(tests)
