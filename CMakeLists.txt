project(music_classifier)
cmake_minimum_required(VERSION 2.8)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}")

aux_source_directory(. SRC_LIST)
aux_source_directory(./audioLoaders SRC_LIST)
aux_source_directory(./audioSavers SRC_LIST)
aux_source_directory(./fastFourierTransform SRC_LIST)
aux_source_directory(./audioDescriptors SRC_LIST)
aux_source_directory(./audioTransforms SRC_LIST)
aux_source_directory(./basicClasses SRC_LIST)
aux_source_directory(./audioExceptions SRC_LIST)
aux_source_directory(./specialFunctions SRC_LIST)
aux_source_directory(./waveletTransform SRC_LIST)

find_package(GSL REQUIRED)
include_directories(${GSL_INCLUDE_DIRS} ${GSLCBLAS_INCLUDE_DIRS})
set(LIBS ${LIBS} ${GSL_LIBRARIES} ${GSLCBLAS_LIBRARIES})
#target_link_libraries(${LIBS})
link_libraries(${LIBS})

add_executable(${PROJECT_NAME} ${SRC_LIST})
include_directories(. ./audioLoaders ./audioSavers ./fastFourierTransform ./audioDescriptors ./audioTransforms ./basicClasses ./audioExceptions ./specialFunctions ./waveletTransform)

#set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall")
set( CMAKE_CXX_FLAGS "-O3")

