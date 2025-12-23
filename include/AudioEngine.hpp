#pragma once

#include "AudioBuffer.hpp"
#include "IAudioDevice.hpp"
#include "IAudioDriver.hpp"
#include "PedalChain.hpp"

#include <memory>
#include <string>

#define DEFAULT_AUDIOBUFFER_CAPACITY 44100

enum class EngineState {
    RUNNING,
    STOPPED
};

class AudioEngine {
public:
    AudioEngine(std::shared_ptr<PedalChain> pedals);

    ~AudioEngine();

    EngineState getState();

    void setInputDevice(const IAudioDriver* driver, const std::string& inputDeviceName);

    void setOutputDevice(const IAudioDriver* driver, const std::string& outputDeviceName);

    void readCallbackHandler(AudioBlock& block);

    void writeCallbackHandler(AudioBlock& block);

    void startStreams();

    void stopStreams();

private:
    std::atomic<EngineState> m_state;

    AudioRingBuffer m_buffer;

    std::unique_ptr<IAudioDevice> m_inputDevice;

    std::unique_ptr<IAudioDevice> m_outputDevice;

    std::shared_ptr<PedalChain> m_pedalChain;
};
