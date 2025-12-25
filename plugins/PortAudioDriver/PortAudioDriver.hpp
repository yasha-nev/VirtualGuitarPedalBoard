#pragma once

#include "IAudioDevice.hpp"
#include "IAudioDriver.hpp"

#include <iostream>
#include <list>
#include <memory>
#include <portaudio.h>
#include <stdexcept>
#include <string>

class PortAudioInputDevice: public IAudioDevice {
public:
    explicit PortAudioInputDevice(
        PaDeviceIndex index,
        std::function<void(AudioBlock& block)> readhandler);

    ~PortAudioInputDevice() override;

    void openStream();

    void startStream() override;

    void stopStream() override;

    const AudioFormat& getFormat() const noexcept override;

private:
    static int readCallback(
        const void* inputBuffer,
        void* outputBuffer,
        unsigned long frameCount,
        const PaStreamCallbackTimeInfo* timeInfo,
        PaStreamCallbackFlags statusFlags,
        void* userData);

    bool m_active;

    PaStream* m_stream;

    PaDeviceIndex m_deviceIndex;

    AudioFormat m_format;

    std::function<void(AudioBlock& block)> m_readhandler;

    PaStreamParameters m_inputParameters;
};

class PortAudioOutputDevice: public IAudioDevice {
public:
    explicit PortAudioOutputDevice(
        PaDeviceIndex index,
        std::function<void(AudioBlock& block)> writeHandler);

    ~PortAudioOutputDevice() override;

    void openStream();

    void startStream() override;

    void stopStream() override;

    const AudioFormat& getFormat() const noexcept override;

private:
    static int writeCallback(
        const void* inputBuffer,
        void* outputBuffer,
        unsigned long frameCount,
        const PaStreamCallbackTimeInfo* timeInfo,
        PaStreamCallbackFlags statusFlags,
        void* userData);

    bool m_active;

    PaStream* m_stream;

    PaDeviceIndex m_deviceIndex;

    AudioFormat m_format;

    PaStreamParameters m_outputParameters;

    std::function<void(AudioBlock& block)> m_writeHandler;
};

class PortAudioDriver: public IAudioDriver {
public:
    PortAudioDriver();

    ~PortAudioDriver() override;

    PaDeviceIndex getDeviceIndex(const std::string& device) const;

    std::list<std::string> getInputDeviceList() override;

    std::list<std::string> getOutputDeviceList() override;

    std::unique_ptr<IAudioDevice> getInputDevice(
        const std::string& inputDeviceName,
        std::function<void(AudioBlock& block)> inputCallback) const override;

    std::unique_ptr<IAudioDevice> getOutputDevice(
        const std::string& outputDeviceName,
        std::function<void(AudioBlock& block)> inputCallback) const override;

private:
    PaDeviceIndex m_defaultInput;
    PaDeviceIndex m_defaultOutput;
};
