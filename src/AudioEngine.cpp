#include "AudioEngine.hpp"

#include <iostream>

AudioEngine::AudioEngine(const std::unique_ptr<PedalChain>& pedals):
    m_buffer(AudioFormat(), 44100),
    m_inputDevice(nullptr),
    m_outputDevice(nullptr),
    m_driver(nullptr),
    m_pedalChain(pedals) {
}

void AudioEngine::setInputDevice(const std::string& inputDeviceName) {
    if(m_driver == nullptr) {
        return;
    }

    m_inputDevice = m_driver->getInputDevice(
        inputDeviceName, [this](AudioBlock& block) { this->readCallbackHandler(block); });
}

void AudioEngine::setOutputDevice(const std::string& outputDeviceName) {
    if(!m_driver) {
        return;
    }

    m_outputDevice = m_driver->getOutputDevice(
        outputDeviceName, [this](AudioBlock& block) { this->writeCallbackHandler(block); });
}

void AudioEngine::setAudioDriver(IAudioDriver* driver) {
    if(!driver) {
        return;
    }
    m_driver = driver;
}

void AudioEngine::readCallbackHandler(AudioBlock& block) {
    // m_pedalChain->process(block);
    m_buffer.push(block);
}

void AudioEngine::writeCallbackHandler(AudioBlock& block) {
    m_buffer.pop(block);
}
