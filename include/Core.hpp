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

    std::list<std::string> getDeviceList();

    void loadPlugins(const std::string& pluginsDir);

    void chooseInputDevice(const std::string& device);

    void chooseOutputtDevice(const std::string& device);

    void start();

    void stop();

private:
    std::list<std::unique_ptr<AudioDriverPlugin>> m_plugins;

    std::unique_ptr<PedalChain> m_pedalChain;

    AudioEngine m_engine;
};
