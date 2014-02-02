project(music_classifier)
cmake_minimum_required(VERSION 2.8)
aux_source_directory(. SRC_LIST)
aux_source_directory(./audioLoaders SRC_LIST)
aux_source_directory(./audioSavers SRC_LIST)
aux_source_directory(./fastFourierTransform SRC_LIST)
add_executable(${PROJECT_NAME} ${SRC_LIST})
include_directories(. ./audioLoaders ./audioSavers ./fastFourierTransform)

