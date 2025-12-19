#pragma once

enum class PedalType { BASE, DISTORTION, DELAY, CHORUS };

#include "AudioBuffer.hpp"

#include <memory>

class IBasePedal {
public:
    virtual ~IBasePedal() = default;

    virtual void process(AudioBlock& block) = 0;

    virtual void tongle() = 0;

protected:
    PedalType m_type;
    bool m_active;
};
