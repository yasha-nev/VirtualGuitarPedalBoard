#pragma once

#include "AudioBuffer.hpp"

enum class PedalType { BASE, DISTORTION, DELAY, CHORUS };

class IBasePedal {
public:
    virtual ~IBasePedal() = default;

    virtual void process(AudioBlock& block) = 0;

    virtual AudioFormat getFormat() const noexcept = 0;

    virtual void setFormat(AudioFormat format) = 0;

    virtual bool isActive() {
        return m_active;
    }

    virtual void tongle() {
        m_active = !m_active;
    }

protected:
    PedalType m_type;

    AudioFormat m_format;

    bool m_active;
};
