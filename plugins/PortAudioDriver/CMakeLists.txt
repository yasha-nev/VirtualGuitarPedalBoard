project(PortAudioDriver LANGUAGES C CXX)

include(FetchContent)

FetchContent_Declare(
    portaudio GIT_REPOSITORY https://github.com/PortAudio/portaudio.git
    GIT_TAG master
)

FetchContent_MakeAvailable(portaudio)

add_library(PortAudioDriver SHARED PortAudioDriver.cpp PortAudioDriver.hpp)

target_include_directories(PortAudioDriver PRIVATE ${CMAKE_SOURCE_DIR}/include)

target_link_libraries(PortAudioDriver PRIVATE portaudio)

set_target_properties(PortAudioDriver PROPERTIES CXX_STANDARD 20)
