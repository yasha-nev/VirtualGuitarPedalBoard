#pragma once

#include "AudioBuffer.hpp"
#include "IAudioDevice.hpp"

#include <functional>
#include <list>
#include <memory>
#include <string>

class IAudioDriver {
public:
    virtual ~IAudioDriver() = default;

    virtual std::list<std::string> getInputDeviceList() = 0;

    virtual std::list<std::string> getOutputDeviceList() = 0;

    virtual std::unique_ptr<IAudioDevice> getInputDevice(
        const std::string& inputDeviceName,
        std::function<void(AudioBlock& block)> readhandler) const = 0;

    virtual std::unique_ptr<IAudioDevice> getOutputDevice(
        const std::string& outputDeviceName,
        std::function<void(AudioBlock& block)> writeHandler) const = 0;
};
