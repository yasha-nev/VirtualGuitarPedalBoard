#include "AudioDriverPlugin.hpp"

AudioDriverPlugin::AudioDriverPlugin(const std::string& path):
    m_driver(nullptr, nullptr) {

    m_handle = dlopen(path.c_str(), RTLD_NOW);
    if(!m_handle) {
        throw std::runtime_error(dlerror());
    }

    m_create = reinterpret_cast<IAudioDriver* (*) ()>(dlsym(m_handle, "createDriver"));
    m_destroy = reinterpret_cast<void (*)(IAudioDriver*)>(dlsym(m_handle, "destroyDriver"));
    if(!m_create || !m_destroy) {
        throw std::runtime_error("Invalid plugin");
    }

    m_driver = std::unique_ptr<IAudioDriver, void (*)(IAudioDriver*)>(m_create(), m_destroy);
}

IAudioDriver* AudioDriverPlugin::getDriver() {
    return m_driver.get();
}
