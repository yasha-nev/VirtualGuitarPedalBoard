#pragma once

#include "AudioBuffer.hpp"

enum class DeviceType { INPUT, OUTPUT };

class IAudioDevice {
public:
    virtual ~IAudioDevice() = default;

    virtual void startStream() = 0;

    virtual void stopStream() = 0;

    virtual const AudioFormat& getFormat() const = 0;

protected:
    DeviceType m_type;
};
