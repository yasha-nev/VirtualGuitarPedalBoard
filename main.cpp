
#include "Core.hpp"

#include <iostream>

int main() {

    Core core("/Users/yasha_nev/Projects/virtualGuitarPedalBoard/build/plugins");

    auto deviceList = core.getDeviceList();

    for (const auto &device : deviceList) {
        std::cout << device << "\n";
    }

    core.chooseInputDevice("Scarlett Solo USB");
    core.chooseOutputtDevice("Динамики MacBook Pro");

    core.start();

    while(getchar() != 's') {
        core.stop();
    }

    return 0;
}