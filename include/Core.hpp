#pragma once

#include "AudioDriverPlugin.hpp"
#include "AudioEngine.hpp"
#include "PedalChain.hpp"

#include <filesystem>
#include <list>
#include <memory>
#include <string>

class Core {
public:
    Core(const std::string& pluginsDir);

    const std::list<std::string>& getInputDeviceList() const noexcept;

    const std::list<std::string>& getOutputDeviceList() const noexcept;

    void loadPlugins(const std::string& pluginsDir);

    void chooseInputDevice(const std::string& device);

    void chooseOutputDevice(const std::string& device);

    void insertPedalByIndex(std::unique_ptr<IBasePedal> pedal, size_t index);

    void deletePedalByIndex(size_t index);

    void start();

    void stop();

private:
    IAudioDriver* findDriverByDeviceName(const std::string& device, DeviceType type);

    bool m_inputDeviceChoosen;

    bool m_outputDeviceChoosen;

    std::list<std::unique_ptr<AudioDriverPlugin>> m_plugins;

    std::list<std::string> m_inputDeviceList;

    std::list<std::string> m_outputDeviceList;

    std::shared_ptr<PedalChain> m_pedalChain;

    AudioEngine m_engine;
};
