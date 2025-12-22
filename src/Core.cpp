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

std::list<std::string> Core::getInputDeviceList() {
    std::list<std::string> deviceList;

    for (const auto& plugin : m_plugins) {

        IAudioDriver *driver = plugin->getDriver();

        auto driverDeviceList = driver->getInputDeviceList();

        deviceList.insert(deviceList.cend(), driverDeviceList.cbegin(), driverDeviceList.cend());
    }

    return deviceList;
}

std::list<std::string> Core::getOutputDeviceList() {
    std::list<std::string> deviceList;

    for (const auto& plugin : m_plugins) {

        IAudioDriver *driver = plugin->getDriver();

        auto driverDeviceList = driver->getOutputDeviceList();

        deviceList.insert(deviceList.cend(), driverDeviceList.cbegin(), driverDeviceList.cend());
    }

    return deviceList;
}

IAudioDriver* Core::findDriverByDeviceName (
    const std::string& device,
    DeviceType type
) {
    for (const auto& plugin : m_plugins) {
        IAudioDriver* driver = plugin->getDriver();

        const auto devices = (type == DeviceType::INPUT) ? driver->getInputDeviceList() : driver->getOutputDeviceList();

        if (std::find(devices.begin(), devices.end(), device) != devices.end()) {
            return driver;
        }
    }
    return nullptr;
}

void Core::chooseInputDevice(const std::string& device) {
    IAudioDriver *driver = findDriverByDeviceName(device, DeviceType::INPUT);

    if (driver) {
        m_engine.setInputDevice(driver, device);
    }
}

void Core::chooseOutputtDevice(const std::string& device) {
    IAudioDriver *driver = findDriverByDeviceName(device, DeviceType::OUTPUT);

    if (driver) {
        m_engine.setOutputDevice(driver, device);
    }
}

void Core::start() {
    m_engine.startStreams();
}

void Core::stop() {
    m_engine.stopStreams();
}
