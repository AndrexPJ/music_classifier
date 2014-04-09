project(music_classifier)
cmake_minimum_required(VERSION 2.8)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}")

set(FEATURE_LIB_DIR ./featureExtractionLibraries)
set(CLASSIFICATION_LIB_DIR ./classificationLibraries)

aux_source_directory(. SRC_LIST)
aux_source_directory(./audioLoaders SRC_LIST)
aux_source_directory(./audioSavers SRC_LIST)
aux_source_directory(./basicClasses SRC_LIST)
aux_source_directory(./audioExceptions SRC_LIST)
aux_source_directory(./tools SRC_LIST)



aux_source_directory(${FEATURE_LIB_DIR}/fastFourierTransform SRC_LIST)
aux_source_directory(${FEATURE_LIB_DIR}/audioDescriptors SRC_LIST)
aux_source_directory(${FEATURE_LIB_DIR}/audioTransforms SRC_LIST)
aux_source_directory(${FEATURE_LIB_DIR}/specialFunctions SRC_LIST)
aux_source_directory(${FEATURE_LIB_DIR}/waveletTransform SRC_LIST)

aux_source_directory(${CLASSIFICATION_LIB_DIR} SRC_LIST)

find_package(OpenCV REQUIRED)
find_package(GSL REQUIRED)
find_package(FFTW REQUIRED)
find_package(Boost REQUIRED COMPONENTS system filesystem)

include_directories(
    ${GSL_INCLUDE_DIRS}
    ${GSLCBLAS_INCLUDE_DIRS}
    ${FFTW_INCLUDE_DIR}
    ${OpenCV_INCLUDE_DIRS}
    ${Boost_INCLUDE_DIRS}
)

set(LIBS ${LIBS} ${GSL_LIBRARIES} ${GSLCBLAS_LIBRARIES} ${FFTW_LIB} ${OpenCV_LIBS} ${Boost_LIBRARIES})

link_libraries(${LIBS})
add_executable(${PROJECT_NAME} ${SRC_LIST})
#target_link_libraries(${PROJECT_NAME} ${LIBS})

include_directories(
    .
    ./audioLoaders
    ./audioSavers
    ./basicClasses
    ./audioExceptions
    ./tools
    ${FEATURE_LIB_DIR}/audioDescriptors
    ${FEATURE_LIB_DIR}/audioTransforms
    ${FEATURE_LIB_DIR}/fastFourierTransform
    ${FEATURE_LIB_DIR}/specialFunctions
    ${FEATURE_LIB_DIR}/waveletTransform
)

#set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall")
set( CMAKE_CXX_FLAGS "-O3")

