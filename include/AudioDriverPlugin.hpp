#pragma once

#include "IAudioDriver.hpp"

#include <dlfcn.h>
#include <iostream>
#include <memory>

class AudioDriverPlugin {
public:
    AudioDriverPlugin(const std::string& path);

    IAudioDriver* getDriver();

private:
    void* m_handle = nullptr;

    IAudioDriver* (*m_create)() = nullptr;

    void (*m_destroy)(IAudioDriver*) = nullptr;

    std::unique_ptr<IAudioDriver, void (*)(IAudioDriver*)> m_driver;
};
