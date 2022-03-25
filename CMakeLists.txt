cmake_minimum_required(VERSION 3.0.0)
project(LinesInTextFiles VERSION 0.1.0)

include(CTest)
enable_testing()

add_executable(LinesInTextFiles LinesInTextFiles.cpp)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)


# add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/libs/mio")
add_subdirectory(libs/mio)
# target_link_libraries( LinesInTextFiles PUBLIC <mio::mio | mio> )
target_link_libraries( LinesInTextFiles PUBLIC mio )


# #Boost::filesystem
# add_subdirectory(libs/filesystem)
# # target_link_libraries( LinesInTextFiles PUBLIC <mio::mio | mio> )
# target_link_libraries( LinesInTextFiles PUBLIC BoostFilesystem )

#Boost::filesystem
# add_subdirectory(libs/SSVUtils)
# # target_link_libraries( LinesInTextFiles PUBLIC <mio::mio | mio> )
# target_link_libraries( LinesInTextFiles PUBLIC BoostFilesystem )
# SSVUtils

target_include_directories(LinesInTextFiles PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/libs/")
target_include_directories(LinesInTextFiles PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include/")

# if(MINGW)
# target_link_libraries(LinesInTextFiles ws2_32)
target_link_libraries(LinesInTextFiles PUBLIC ws2_32) # can use like -lws2_32 gcc
# endif()

# target_link_libraries(LinesInTextFiles PUBLIC OpenMP)
# find_package(OpenMP)
# if(OpenMP_CXX_FOUND)
#     target_link_libraries(LinesInTextFiles PUBLIC OpenMP)
# endif()
find_package(OpenMP REQUIRED)
target_link_libraries(LinesInTextFiles PRIVATE OpenMP::OpenMP_CXX)

# /// Static link libstdc
# target_link_options(LinesInTextFiles PRIVATE -static-libgcc -static-libstdc++)












# target_link_libraries(solver PRIVATE "${OpenMP_CXX_FLAGS}")
# target_compile_options(solver PRIVATE "${OpenMP_CXX_FLAGS}")

# set(CMAKE_C_FLAGS_DEBUG "-g -DDEBUG")
# set(CMAKE_CXX_FLAGS_DEBUG "-g -DDEBUG")

# CMAKE_TOOLCHAIN_FILE=D:\src\vcpkg\scripts\buildsystems\vcpkg.cmake
# set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake"
# CACHE STRING "")

# target_include_directories(LinesInTextFiles PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/libs/SSVUtils/include/")
# target_include_directories(LinesInTextFiles PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/libs/SSVUtils/extlibs/vrm_pp/include/")
# libs\SSVUtils\extlibs\vrm_pp\include
# set( CMAKE_CXX_FLAGS "-lstdc++fs" )
# set( CMAKE_CXX_FLAGS "-std=c++17 -lstdc++fs" )
#-std=c++17 ... -lstdc++fs

# file(GLOB TestLink_SRC
#      "*.h"
#      "*.cpp"
#      "${CMAKE_CURRENT_SOURCE_DIR}/Data/*.h"
#      "${CMAKE_CURRENT_SOURCE_DIR}/Data/*.cpp"
#      "${CMAKE_CURRENT_SOURCE_DIR}/Filters/*.h"
#      "${CMAKE_CURRENT_SOURCE_DIR}/Filters/*.cpp"
# )

# # file(GLOB TestLink CONFIGURE_DEPENDS "*.h" "*.cpp")

# message("${TestLink_SRC}")


# add_executable(TestLink main.cpp ${TestLink_SRC})


#pragma once
#ifndef LINALG_H
#define LINALG_H

#endif ///LINALG_H







####################################################################################





# cmake_minimum_required(VERSION 3.0.0)
# project(TestLinkOpenGL1 VERSION 0.1.0)

# include(CTest)
# enable_testing()

# #add_executable(TestLinkOpenGL1 main.cpp)
# #add_executable(TestLinkOpenGL1 hello_triangle.cpp)

# #add_executable(TestLinkOpenGL1 ${CMAKE_CURRENT_SOURCE_DIR}/learnopengl/hello_triangle.cpp)

# #add_executable(TestLinkOpenGL1 ${CMAKE_CURRENT_SOURCE_DIR}/learnopengl/textures.cpp)

# #add_executable(TestLinkOpenGL1 ${CMAKE_CURRENT_SOURCE_DIR}/learnopengl/shaders_class.cpp)

# #add_executable(TestLinkOpenGL1 ${CMAKE_CURRENT_SOURCE_DIR}/learnopengl/camera_class.cpp)

# add_executable(TestLinkOpenGL1 ${CMAKE_CURRENT_SOURCE_DIR}/learnopengl/flag.cpp)

# #add_executable(TestLinkOpenGL1 ${CMAKE_CURRENT_SOURCE_DIR}/learnopengl/compute.cpp)

# #add_executable(TestLinkOpenGL1 ${CMAKE_CURRENT_SOURCE_DIR}/learnopengl/compute2.cpp)

# #target_include_directories(ZMQTestServer PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/Include/")

# #target_link_libraries(ZMQTestServer "${CMAKE_CURRENT_SOURCE_DIR}/lib/libzmq-v142-mt-4_3_2.lib")

# ### Work #
# #add_subdirectory(glad)
# #target_link_libraries(TestLinkOpenGL1 GLAD)
# ###

# #target_include_directories(TestLinkOpenGL1 PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/glad/")

# #include/glad/glad.h
# #include/KHR/khrplatform.h
# #src/glad.c

# #target_include_directories(TestLinkOpenGL1 PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/glad/KHR/")

# #target_include_directories(TestLinkOpenGL1 PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/glad/")

# ### Work #
# add_subdirectory(glad)
# target_link_libraries(TestLinkOpenGL1 GLAD)

# add_subdirectory(SDL_image-main/external/libpng-1.6.37/)
# target_include_directories(TestLinkOpenGL1 PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/SDL_image-main/external/libpng-1.6.37/")
# # target_link_libraries(TestLinkOpenGL1 "${CMAKE_CURRENT_SOURCE_DIR}/SDL_image-main/external/libpng-1.6.37/build/libpng.a")
# target_link_libraries(TestLinkOpenGL1 "${CMAKE_CURRENT_SOURCE_DIR}/SDL_image-main/external/libpng-1.6.37/build/libpng16d.dll.a")
# # target_link_libraries(TestLinkOpenGL1 "${CMAKE_CURRENT_SOURCE_DIR}/SDL_image-main/external/libpng-1.6.37/build/libpng.a")


# # add_subdirectory(SDL-main)
# # target_include_directories(TestLinkOpenGL1 PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/SDL-main/")
# # target_include_directories(TestLinkOpenGL1 PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/SDL-main/include/")

# # add_subdirectory(SDL_image-main)
# # target_include_directories(TestLinkOpenGL1 PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/SDL_image-main/")
# ### Work?
# #add_subdirectory(lpng1637)

# #lpng1637
# #target_include_directories(TestLinkOpenGL1 PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/lpng1637/lpng1637/")
# #target_include_directories(TestLinkOpenGL1 PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/lib/lpng1515/lpng1515/")
# #target_link_libraries(TestLinkOpenGL1 png.a)
# #D:\Cpp\TestLinkOpenGL\lib\lpng1515\lpng1515
# #add_subdirectory(glfw-3.3/glfw-3.3/)

# target_include_directories(TestLinkOpenGL1 PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/Include/")

# #target_include_directories(TestLinkOpenGL1 PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/Include/")

# #target_link_libraries(TestLinkOpenGL1 "${CMAKE_CURRENT_SOURCE_DIR}/lib/glfw3.lib")

# target_link_libraries(TestLinkOpenGL1 "${CMAKE_CURRENT_SOURCE_DIR}/lib/mingwGlfw/libglfw3.a")

# #target_include_directories(TestLinkOpenGL1 PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/glfw-3.3/glfw-3.3/")

# target_include_directories(TestLinkOpenGL1 PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/learnopengl/")
# #add_executable(TestLinkOpenGL1 ${CMAKE_CURRENT_SOURCE_DIR}/learnopengl/shaders_class.cpp)


# #D:\Cpp\TestLinkOpenGL\Include\sail-master\sail-master
# #target_include_directories(TestLinkOpenGL1 PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/Include/sail-master/sail-master/")
# #target_include_directories(TestLinkOpenGL1 PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/Include/sail-master/sail-master/")
# #target_include_directories(TestLinkOpenGL1 PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/Include/sail-master/sail-master/")
# #target_include_directories(TestLinkOpenGL1 PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/Include/sail-master/sail-master/")

# #target_include_directories(TestLinkOpenGL1 PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/Include/sail-master/sail-master/src/")


# #add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/Include/sail-master/sail-master/")
# #target_link_libraries(TestLinkOpenGL1 SAIL)


# set(CPACK_PROJECT_NAME ${PROJECT_NAME})
# set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
# include(CPack)




# # file(GLOB TestLink_SRC
# #      "*.h"
# #      "*.cpp"
# #      "${CMAKE_CURRENT_SOURCE_DIR}/Data/*.h"
# #      "${CMAKE_CURRENT_SOURCE_DIR}/Data/*.cpp"
# #      "${CMAKE_CURRENT_SOURCE_DIR}/Filters/*.h"
# #      "${CMAKE_CURRENT_SOURCE_DIR}/Filters/*.cpp"
# # )

# # # file(GLOB TestLink CONFIGURE_DEPENDS "*.h" "*.cpp")

# # message("${TestLink_SRC}")


# # add_executable(TestLink main.cpp ${TestLink_SRC})


# #pragma once
# #ifndef LINALG_H
# #define LINALG_H

# #endif ///LINALG_H