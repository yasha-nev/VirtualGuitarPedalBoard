cmake_minimum_required(VERSION 4.1.1)

project(vgp VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED YES)

include_directories(
    include
    include/pedals
    
    src
    src/pedals
    )

set(SRCS
    src/AudioBuffer.cpp
    src/AudioDriverPlugin.cpp
    src/AudioEngine.cpp
    src/Core.cpp
    src/PedalChain.cpp
    src/pedals/ChorusPedal.cpp
    src/pedals/DelayPedal.cpp
    src/pedals/DistortionPedal.cpp
    )

set(HEADERS
    include/AudioBuffer.hpp
    include/AudioDriverPlugin.hpp
    include/AudioEngine.hpp
    include/Core.hpp
    include/IAudioDriver.hpp
    include/IAudioDevice.hpp
    include/PedalChain.hpp
    include/pedals/IBasePedal.hpp
    include/pedals/ChorusPedal.hpp
    include/pedals/DelayPedal.hpp
    include/pedals/DistortionPedal.hpp
    )

#add_compile_options(-Wall -Wextra)

#===========LIBRARY=================
add_library(vgp STATIC ${SRCS} ${HEADERS})

#===============VGP==================
add_executable(main main.cpp)
target_link_libraries(main PRIVATE vgp)

add_subdirectory(plugins)
