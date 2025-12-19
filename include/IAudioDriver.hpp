#pragma once

#include "AudioBuffer.hpp"
#include "IAudioDevice.hpp"

#include <list>
#include <string>

class IAudioDriver {
public:
    virtual ~IAudioDriver() = default;

    virtual std::list<std::string> getDeviceList() = 0;

    virtual std::unique_ptr<IAudioDevice> getInputDevice(
        const std::string& inputDeviceName,
        std::function<void(AudioBlock& block)> readhandler) = 0;

    virtual std::unique_ptr<IAudioDevice> getOutputDevice(
        const std::string& outputDeviceName,
        std::function<void(AudioBlock& block)> writeHandler) = 0;
};
