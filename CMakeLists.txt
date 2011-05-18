# Build configuration file for testing the proposed QVM Boost library
# 2011-05-17 Jeff Trull <jetrull@sbcglobal.net>
# You need to specify the locations of three libraries: the proposed QVM, plus the OpenCollada
# 3D scene description parsing library and the Ogre3D rendering library, using BOOST_QVM_DIR,
# COLLADA_DIR, and OGRE_DIR in the CMake GUI or on the command line.  In Unix it looks like this:
# mkdir build;cd build;cmake -DBOOST_QVM_DIR=/home/jet/boostcon/2011/LIAW/boost-qvm \
#                            -DCOLLADA_DIR=/home/jet/boostcon/2011/LIAW/opencollada-read-only \
#                            -DOGRE_DIR=/usr/lib/OGRE ..;make

cmake_minimum_required(VERSION 2.6)

project(qvm_test)

if(OGRE_DIR)
    # Look under this directory to find FindOGRE.cmake etc.
    set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${OGRE_DIR}/cmake)
endif()

find_package(OGRE REQUIRED)

find_package(Boost REQUIRED COMPONENTS ${OGRE_BOOST_COMPONENTS})

include_directories(${Boost_INCLUDE_DIR} ${OGRE_INCLUDE_DIRS} ${BOOST_QVM_DIR} ${COLLADA_DIR}/COLLADABaseUtils/include)

link_directories(${COLLADA_DIR}/lib)
add_executable(test WIN32 main.cpp)
target_link_libraries(test ${OGRE_LIBRARIES} ${Boost_LIBRARIES} OpenCOLLADABaseUtils )
