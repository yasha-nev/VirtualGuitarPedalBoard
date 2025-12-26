#pragma once

#include "IBasePedal.hpp"

class DistortionPedal: public IBasePedal {
public:
    DistortionPedal(float dist = 0.0f, float tone = 0.0f, float level = 0.0f);

    void setDist(float dist);

    void setTone(float tone);

    void setLevel(float level);

    void setFormat(AudioFormat format) override;

    float getDist() const noexcept;

    float getTone() const noexcept;

    float getLevel() const noexcept;

    AudioFormat getFormat() const noexcept override;

    void process(AudioBlock& block) override;

private:
    float preFilter(float x, float last);

    float clip(float x);

    float toneFilter(float x, float last);

    float m_tone;

    float m_dist;

    float m_level;

    std::vector<float> m_lastSamplePre { 2, 0.0f };

    std::vector<float> m_lastSampleTone { 2, 0.0f };
};
