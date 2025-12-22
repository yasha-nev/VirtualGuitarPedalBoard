#include "AudioEngine.hpp"

#include <iostream>

AudioEngine::AudioEngine(const std::unique_ptr<PedalChain>& pedals):
    m_buffer(AudioFormat(), 44100),
    m_inputDevice(nullptr),
    m_outputDevice(nullptr),
    m_pedalChain(pedals) {
}

void AudioEngine::setInputDevice(const IAudioDriver* driver, const std::string& inputDeviceName) {
    if(driver == nullptr) {
        return;
    }

    m_inputDevice = driver->getInputDevice(
        inputDeviceName, [this](AudioBlock& block) { this->readCallbackHandler(block); });
}

void AudioEngine::setOutputDevice(const IAudioDriver* driver, const std::string& outputDeviceName) {
    if(!driver) {
        return;
    }

    m_outputDevice = driver->getOutputDevice(
        outputDeviceName, [this](AudioBlock& block) { this->writeCallbackHandler(block); });
}

void AudioEngine::readCallbackHandler(AudioBlock& block) {
    // m_pedalChain->process(block);
    m_buffer.push(block);
}

void AudioEngine::writeCallbackHandler(AudioBlock& block) {
    m_buffer.pop(block);
}


void AudioEngine::startStreams() {
    m_buffer.setFormat(m_outputDevice->getFormat());
    m_inputDevice->startStream();
    m_outputDevice->startStream();
}

void AudioEngine::stopStreams() {
    m_inputDevice->stopStream();
    m_outputDevice->stopStream();
}