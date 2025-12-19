#include "Core.hpp"

#if defined(_WIN32)
constexpr const char* PLUGIN_EXT = ".dll";
#elif defined(__APPLE__)
constexpr const char* PLUGIN_EXT = ".dylib";
#else
constexpr const char* PLUGIN_EXT = ".so";
#endif

Core::Core(const std::string& pluginsDir):
    m_pedalChain(nullptr),
    m_engine(m_pedalChain) {

    loadPlugins(pluginsDir);

    auto& plugin = m_plugins.front();

    m_engine.setAudioDriver(plugin->getDriver());
}

std::list<std::string> Core::getDeviceList() {
    std::list<std::string> deviceList;

    for(const auto& plugin: m_plugins) {
        IAudioDriver* driver = plugin->getDriver();
        for(const auto& device: driver->getDeviceList()) {
            deviceList.push_back(device);
        }
    }

    return deviceList;
}

void Core::loadPlugins(const std::string& pluginsDir) {

    if(!std::filesystem::exists(pluginsDir) || !std::filesystem::is_directory(pluginsDir)) {
        return;
    }

    for(const auto& entry: std::filesystem::recursive_directory_iterator(pluginsDir)) {
        if(!entry.is_regular_file()) {
            continue;
        }

        if(entry.path().extension() == PLUGIN_EXT) {
            try {
                m_plugins.emplace_back(std::make_unique<AudioDriverPlugin>(entry.path()));
            } catch(const std::exception& e) {
                std::cerr << "Failed to load plugin " << entry.path() << ": " << e.what() << '\n';
            }
        }
    }
}

void Core::chooseInputDevice(const std::string& device) {
    m_engine.setInputDevice(device);
}

void Core::chooseOutputtDevice(const std::string& device) {
    m_engine.setOutputDevice(device);
}

void Core::start() {
    m_engine.start();
}

void Core::stop() {
    m_engine.stop();
}
