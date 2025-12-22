#pragma once

#include "AudioBuffer.hpp"
#include "IAudioDevice.hpp"
#include "IAudioDriver.hpp"
#include "PedalChain.hpp"

#include <memory>
#include <string>

class AudioEngine {
public:
    AudioEngine(const std::unique_ptr<PedalChain>& pedals);

    void setInputDevice(const IAudioDriver* driver, const std::string& inputDeviceName);

    void setOutputDevice(const IAudioDriver* driver, const std::string& outputDeviceName);

    void readCallbackHandler(AudioBlock& block);

    void writeCallbackHandler(AudioBlock& block);

    void startStreams();

    void stopStreams();

private:
    AudioRingBuffer m_buffer;

    std::unique_ptr<IAudioDevice> m_inputDevice;

    std::unique_ptr<IAudioDevice> m_outputDevice;

    const std::unique_ptr<PedalChain>& m_pedalChain;
};
