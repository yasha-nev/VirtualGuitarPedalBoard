#pragma once

enum class PedalType { BASE, DISTORTION, DELAY, CHORUS };

#include "AudioBuffer.hpp"

class IBasePedal {
public:
    virtual ~IBasePedal() = default;

    virtual void process(AudioBlock& block) = 0;

    virtual bool isActive() { return m_active; }

    virtual void tongle() { m_active = !m_active; }

protected:
    
    PedalType m_type;
    
    bool m_active;
};
