#include "AudioEngine.hpp"

AudioEngine::AudioEngine(std::shared_ptr<PedalChain> pedals):
    m_state(EngineState::STOPPED),
    m_buffer(AudioFormat(), DEFAULT_AUDIOBUFFER_CAPACITY),
    m_inputDevice(nullptr),
    m_outputDevice(nullptr),
    m_pedalChain(pedals) {
}

AudioEngine::~AudioEngine() {
    stopStreams();
}

EngineState AudioEngine::getState() const noexcept {
    return m_state.load();
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
    if(m_pedalChain) {
        m_pedalChain->process(block);
    }
    m_buffer.push(block);
}

void AudioEngine::writeCallbackHandler(AudioBlock& block) {
    m_buffer.pop(block);
}

void AudioEngine::startStreams() {
    if(m_state == EngineState::RUNNING || !m_inputDevice || !m_outputDevice) {
        return;
    }

    m_buffer.setFormat(m_outputDevice->getFormat());
    m_inputDevice->startStream();
    m_outputDevice->startStream();
    m_state = EngineState::RUNNING;
}

void AudioEngine::stopStreams() {
    if(m_state == EngineState::STOPPED || !m_inputDevice || !m_outputDevice) {
        return;
    }

    m_inputDevice->stopStream();
    m_outputDevice->stopStream();

    m_state = EngineState::STOPPED;
}
