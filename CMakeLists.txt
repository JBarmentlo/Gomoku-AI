cmake_minimum_required(VERSION 3.0.0)

set(CMAKE_CPP_COMPILER g++-10)
set(CMAKE_CXX_COMPILER g++-10)
set(CMAKE_CXX_STANDARD 17)
# set(CMAKE_CXX_FLAGS "-O3")
add_compile_options(-O3)
project(Roobik VERSION 0.1.0)

find_package(Threads REQUIRED)
find_package(OpenSSL REQUIRED)

if(NOT WIN32)
  string(ASCII 27 Esc)
  set(ColourReset "${Esc}[m")
  set(ColourBold  "${Esc}[1m")
  set(Red         "${Esc}[31m")
  set(Green       "${Esc}[32m")
  set(Yellow      "${Esc}[33m")
  set(Blue        "${Esc}[34m")
  set(Magenta     "${Esc}[35m")
  set(Cyan        "${Esc}[36m")
  set(White       "${Esc}[37m")
  set(BoldRed     "${Esc}[1;31m")
  set(BoldGreen   "${Esc}[1;32m")
  set(BoldYellow  "${Esc}[1;33m")
  set(BoldBlue    "${Esc}[1;34m")
  set(BoldMagenta "${Esc}[1;35m")
  set(BoldCyan    "${Esc}[1;36m")
  set(BoldWhite   "${Esc}[1;37m")
endif()

# message("This is normal")
# message("${Red}This is Red${ColourReset}")
# message("${Green}This is Green${ColourReset}")
# message("${Yellow}This is Yellow${ColourReset}")

# include(CTest)
# enable_testing()

set(SOURCES
    src/main.cpp
    src/state.cpp
    src/utils.cpp
    src/eval.cpp
    src/minimax.cpp
    src/pattern.cpp
    src/server_sync.cpp
    # src/test.cpp
)

if(SINGLE_FRED)
  message(STATUS "${Green}SINGLE THREAD OPTION ACTIVATED${ColourReset}")
  add_definitions(-DSINGLE_THREAD)
#   set(SINGLE_FRED ON)
else()
    message(STATUS "${Green}MULTI THREAD OPTION ACTIVATED${ColourReset}") 
endif()



add_executable(Gomook ${SOURCES})

target_include_directories(Gomook
    PRIVATE 
        ${PROJECT_SOURCE_DIR}/include
)


# find_package(PythonLibs REQUIRED)
# include_directories(${PYTHON_INCLUDE_DIRS})
# target_link_libraries(Roobik ${PYTHON_LIBRARIES})

set_property(TARGET Gomook PROPERTY CXX_STANDARD 17)
target_link_libraries(Gomook PRIVATE Threads::Threads)
target_link_libraries(Gomook PRIVATE OpenSSL::SSL)
target_link_libraries(Gomook PRIVATE OpenSSL::Crypto)

# set(CPACK_PROJECT_NAME ${PROJECT_NAME})
# set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
# include(CPack)
