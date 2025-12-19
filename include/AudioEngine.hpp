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

    void setInputDevice(const std::string& inputDeviceName);

    void setOutputDevice(const std::string& outputDeviceName);

    void setAudioDriver(IAudioDriver* driver);

    void readCallbackHandler(AudioBlock& block);

    void writeCallbackHandler(AudioBlock& block);

    void start() {
        m_buffer.setFormat(m_outputDevice->getFormat());

        m_inputDevice->startStream();
        m_outputDevice->startStream();
    }

    void stop() {
        m_inputDevice->stopStream();
        m_outputDevice->stopStream();
    }

private:
    AudioRingBuffer m_buffer;

    std::unique_ptr<IAudioDevice> m_inputDevice;

    std::unique_ptr<IAudioDevice> m_outputDevice;

    IAudioDriver* m_driver;

    const std::unique_ptr<PedalChain>& m_pedalChain;
};
