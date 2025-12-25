#include "PortAudioDriver.hpp"

#define SAMPLE_RATE 44100
#define FRAMES_PER_BUFFER 128

PortAudioInputDevice::PortAudioInputDevice(
    PaDeviceIndex index,
    std::function<void(AudioBlock& block)> readhandler):
    m_active(false),
    m_stream(nullptr),
    m_deviceIndex(index),
    m_readhandler(readhandler) {

    openStream();
}

PortAudioInputDevice::~PortAudioInputDevice() {
    stopStream();
}

int PortAudioInputDevice::readCallback(
    const void* inputBuffer,
    void* outputBuffer,
    unsigned long frameCount,
    const PaStreamCallbackTimeInfo* timeInfo,
    PaStreamCallbackFlags statusFlags,
    void* userData) {
    (void) outputBuffer;
    (void) timeInfo;
    (void) statusFlags;

    PortAudioInputDevice* device = (PortAudioInputDevice*) userData;

    if(!inputBuffer) {
        return paContinue;
    }

    float* audioData = (float*) inputBuffer;

    std::span<float> span(audioData, frameCount * device->m_format.channels);

    AudioBlock block(span, device->m_format, frameCount);

    device->m_readhandler(block);

    return paContinue;
}

void PortAudioInputDevice::openStream() {
    if(m_active) {
        return;
    }

    PaError err;

    const PaDeviceInfo* inputDeviceInfo = Pa_GetDeviceInfo(m_deviceIndex);

    m_inputParameters.device = m_deviceIndex;
    m_inputParameters.channelCount = inputDeviceInfo->maxInputChannels;
    m_inputParameters.sampleFormat = paFloat32;
    m_inputParameters.suggestedLatency = inputDeviceInfo->defaultLowInputLatency / 2;
    m_inputParameters.hostApiSpecificStreamInfo = nullptr;

    m_format.channels = inputDeviceInfo->maxInputChannels;
    m_format.sampleRate = SAMPLE_RATE;
    m_format.type = SampleType::Float32;
    m_format.interleaved = true;

    err = Pa_OpenStream(
        &m_stream,
        &m_inputParameters,
        NULL,
        SAMPLE_RATE,
        FRAMES_PER_BUFFER,
        paClipOff,
        this->readCallback,
        this);

    if(err != paNoError) {
        std::cout << "ERROR, Input stream didn't open\n";
        return;
    }

    std::cout << "Input stream open\n";
}

void PortAudioInputDevice::startStream() {
    if(m_active) {
        return;
    }

    if(!m_stream) {
        openStream();
    }

    PaError err;

    err = Pa_StartStream(m_stream);

    if(err != paNoError) {
        std::cout << "ERROR, Input stream didn't start\n";
        return;
    }

    m_active = true;

    std::cout << "Input stream start\n";
}

void PortAudioInputDevice::stopStream() {
    if(!m_active) {
        return;
    }
    Pa_AbortStream(m_stream);
    Pa_CloseStream(m_stream);

    m_stream = NULL;
    m_active = false;

    std::cout << "Input stream stop\n";
}

const AudioFormat& PortAudioInputDevice::getFormat() const noexcept {
    return m_format;
}

PortAudioOutputDevice::PortAudioOutputDevice(
    PaDeviceIndex index,
    std::function<void(AudioBlock& block)> writeHandler):
    m_active(false),
    m_stream(nullptr),
    m_deviceIndex(index),
    m_writeHandler(writeHandler) {

    openStream();
}

PortAudioOutputDevice::~PortAudioOutputDevice() {
    stopStream();
}

int PortAudioOutputDevice::writeCallback(
    const void* inputBuffer,
    void* outputBuffer,
    unsigned long frameCount,
    const PaStreamCallbackTimeInfo* timeInfo,
    PaStreamCallbackFlags statusFlags,
    void* userData) {

    (void) inputBuffer;
    (void) timeInfo;
    (void) statusFlags;

    PortAudioOutputDevice* device = (PortAudioOutputDevice*) userData;

    if(!outputBuffer) {
        return paContinue;
    }

    float* audioData = (float*) outputBuffer;

    std::span<float> span(audioData, frameCount * device->m_format.channels);

    AudioBlock block(span, device->m_format, frameCount);

    device->m_writeHandler(block);

    return paContinue;
}

void PortAudioOutputDevice::openStream() {
    if(m_active) {
        return;
    }

    const PaDeviceInfo* outputDeviceInfo = Pa_GetDeviceInfo(m_deviceIndex);

    m_outputParameters.device = m_deviceIndex;
    m_outputParameters.channelCount = outputDeviceInfo->maxOutputChannels;
    m_outputParameters.sampleFormat = paFloat32;
    m_outputParameters.suggestedLatency = outputDeviceInfo->defaultLowOutputLatency / 2;
    m_outputParameters.hostApiSpecificStreamInfo = nullptr;

    m_format.channels = outputDeviceInfo->maxOutputChannels;
    m_format.sampleRate = SAMPLE_RATE;
    m_format.type = SampleType::Float32;
    m_format.interleaved = true;

    PaError err = Pa_OpenStream(
        &m_stream,
        NULL,
        &m_outputParameters,
        SAMPLE_RATE,
        FRAMES_PER_BUFFER,
        paClipOff,
        PortAudioOutputDevice::writeCallback,
        this);

    if(err != paNoError) {
        std::cout << "ERROR, Output stream not open\n";
        return;
    }

    std::cout << "Output stream open\n";
}

void PortAudioOutputDevice::startStream() {
    if(m_active) {
        return;
    }

    if(!m_stream) {
        openStream();
    }

    PaError err = Pa_StartStream(m_stream);
    if(err != paNoError) {
        std::cout << "ERROR, Output stream not start\n";
        return;
    }

    m_active = true;

    std::cout << "Output stream start\n";
}

void PortAudioOutputDevice::stopStream() {
    if(!m_active) {
        return;
    }
    Pa_AbortStream(m_stream);
    Pa_CloseStream(m_stream);

    m_stream = NULL;
    m_active = false;

    std::cout << "output stream stop\n";
}

const AudioFormat& PortAudioOutputDevice::getFormat() const noexcept {
    return m_format;
}

PortAudioDriver::PortAudioDriver() {
    PaError err = Pa_Initialize();
    if(err != paNoError) {
        throw std::runtime_error("Pa_Initialize failed");
    }

    m_defaultInput = Pa_GetDefaultInputDevice();
    m_defaultOutput = Pa_GetDefaultOutputDevice();
}

PortAudioDriver::~PortAudioDriver() {
    Pa_Terminate();
}

std::list<std::string> PortAudioDriver::getInputDeviceList() {
    std::list<std::string> devices;

    int count = Pa_GetDeviceCount();

    for(int i = 0; i < count; ++i) {
        const PaDeviceInfo* info = Pa_GetDeviceInfo(i);
        if(info && info->maxInputChannels > 0) {
            devices.emplace_back(info->name);
        }
    }
    return devices;
}

std::list<std::string> PortAudioDriver::getOutputDeviceList() {
    std::list<std::string> devices;

    int count = Pa_GetDeviceCount();

    for(int i = 0; i < count; ++i) {
        const PaDeviceInfo* info = Pa_GetDeviceInfo(i);
        if(info && info->maxOutputChannels > 0) {
            devices.emplace_back(info->name);
        }
    }
    return devices;
}

PaDeviceIndex PortAudioDriver::getDeviceIndex(const std::string& device) const {

    int numDevices = Pa_GetDeviceCount();
    if(numDevices < 0) {
        return -1;
    }

    for(int i = 0; i < numDevices; ++i) {
        const PaDeviceInfo* deviceInfo = Pa_GetDeviceInfo(i);
        if(deviceInfo->name == device) {
            return i;
        }
    }
    return -1;
}

std::unique_ptr<IAudioDevice> PortAudioDriver::getInputDevice(
    const std::string& inputDeviceName,
    std::function<void(AudioBlock& block)> readHandler) const {

    PaDeviceIndex index = getDeviceIndex(inputDeviceName);

    if(index == -1) {
        return nullptr;
    }

    return std::make_unique<PortAudioInputDevice>(index, readHandler);
}

std::unique_ptr<IAudioDevice> PortAudioDriver::getOutputDevice(
    const std::string& outputDeviceName,
    std::function<void(AudioBlock& block)> writeHandler) const {

    PaDeviceIndex index = getDeviceIndex(outputDeviceName);

    if(index == -1) {
        return nullptr;
    }

    return std::make_unique<PortAudioOutputDevice>(index, writeHandler);
}

extern "C" {
IAudioDriver* createDriver() {
    return new PortAudioDriver();
}

void destroyDriver(IAudioDriver* driver) {
    delete driver;
}
}
