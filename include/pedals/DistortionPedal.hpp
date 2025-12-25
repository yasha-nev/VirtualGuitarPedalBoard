#pragma once

#include "IBasePedal.hpp"

class DistortionPedal: public IBasePedal {
public:
    DistortionPedal(float dist = 0.5f, float tone = 0.5f, float level = 0.5f);

    ~DistortionPedal();

    void setDist(float dist);

    void setTone(float tone);

    void setLevel(float level);

    float getDist() const noexcept;

    float getTone() const noexcept;

    float getLevel() const noexcept;

    void process(AudioBlock& block) override;

    void tongle() override;

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
