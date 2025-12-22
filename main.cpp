
#include "Core.hpp"

#include <iostream>

int main() {

    Core core("/Users/yasha_nev/Projects/virtualGuitarPedalBoard/build/plugins");

    std::cout << "Input device list: \n";
    for (const auto &device : core.getInputDeviceList()) {
        std::cout << device << "\n";
    }

    std::cout << "\n";

    std::cout << "Output device list: \n";
    for (const auto &device : core.getOutputDeviceList()) {
        std::cout << device << "\n";
    }

    //core.chooseInputDevice("Scarlett Solo USB");
    //core.chooseOutputtDevice("Динамики MacBook Pro");

    //core.start();

    while(getchar() != 's') {
        //core.stop();
    }

    return 0;
}