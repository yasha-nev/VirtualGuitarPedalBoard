
#include "Core.hpp"
#include "DistortionPedal.hpp"

#include <iostream>

int main() {

    Core core("/Users/yasha_nev/Projects/virtualGuitarPedalBoard/build/plugins");

    std::cout << "Input device list: \n";
    for(const auto& device: core.getInputDeviceList()) {
        std::cout << device << "\n";
    }

    std::cout << "\n";

    std::cout << "Output device list: \n";
    for(const auto& device: core.getOutputDeviceList()) {
        std::cout << device << "\n";
    }

    auto distortion = std::make_unique<DistortionPedal>(0.9f, 0.4f, 0.9f);
    distortion->tongle();

    core.insertPedalByIndex(std::move(distortion), 0);

    core.chooseInputDevice("Scarlett Solo USB");
    core.chooseOutputDevice("Динамики MacBook Pro");

    core.start();

    while(getchar() != 's') {
        core.stop();
    }

    return 0;
}
