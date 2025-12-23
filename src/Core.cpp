#include "Core.hpp"

#if defined(_WIN32)
constexpr const char* PLUGIN_EXT = ".dll";
#elif defined(__APPLE__)
constexpr const char* PLUGIN_EXT = ".dylib";
#else
constexpr const char* PLUGIN_EXT = ".so";
#endif

Core::Core(const std::string& pluginsDir):
    m_inputDeviceChoosen(false),
    m_outputDeviceChoosen(false),
    m_pedalChain(std::make_shared<PedalChain>()),
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

                auto plugin = std::make_unique<AudioDriverPlugin>(entry.path());

                IAudioDriver* driver = plugin->getDriver();

                auto driverDeviceList = driver->getInputDeviceList();
                m_inputDeviceList.insert(
                    m_inputDeviceList.cend(), driverDeviceList.cbegin(), driverDeviceList.cend());

                driverDeviceList = driver->getOutputDeviceList();
                m_outputDeviceList.insert(
                    m_outputDeviceList.cend(), driverDeviceList.cbegin(), driverDeviceList.cend());

                m_plugins.emplace_back(std::move(plugin));

            } catch(const std::exception& e) {
                std::cerr << "Failed to load plugin " << entry.path() << ": " << e.what() << '\n';
            }
        }
    }
}

const std::list<std::string>& Core::getInputDeviceList() const noexcept {
    return m_inputDeviceList;
}

const std::list<std::string>& Core::getOutputDeviceList() const noexcept {
    return m_outputDeviceList;
}

IAudioDriver* Core::findDriverByDeviceName(const std::string& device, DeviceType type) {
    for(const auto& plugin: m_plugins) {
        IAudioDriver* driver = plugin->getDriver();

        const auto devices = (type == DeviceType::INPUT) ? driver->getInputDeviceList() :
                                                           driver->getOutputDeviceList();

        if(std::find(devices.begin(), devices.end(), device) != devices.end()) {
            return driver;
        }
    }
    return nullptr;
}

void Core::chooseInputDevice(const std::string& device) {
    IAudioDriver* driver = findDriverByDeviceName(device, DeviceType::INPUT);

    if(driver) {
        m_engine.setInputDevice(driver, device);
        m_inputDeviceChoosen = true;
    }
}

void Core::chooseOutputDevice(const std::string& device) {
    IAudioDriver* driver = findDriverByDeviceName(device, DeviceType::OUTPUT);

    if(driver) {
        m_engine.setOutputDevice(driver, device);
        m_outputDeviceChoosen = true;
    }
}

void Core::insertPedalByIndex(std::unique_ptr<IBasePedal> pedal, size_t index) {
    m_pedalChain->insertPedalByIndex(std::move(pedal), index);
}

void Core::deletePedalByIndex(size_t index) {
    m_pedalChain->deletePedalByIndex(index);
}

void Core::start() {
    if(!m_inputDeviceChoosen || !m_outputDeviceChoosen) {
        return;
    }

    m_engine.startStreams();
}

void Core::stop() {
    m_engine.stopStreams();
}
