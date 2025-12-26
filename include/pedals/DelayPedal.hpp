#pragma once

#include "IBasePedal.hpp"

class DelayPedal: public IBasePedal {
public:
    explicit DelayPedal(float time = 0.0f, float feedback = 0.0f, float level = 0.0f);

    void setTime(float time);

    void setFeedback(float feedback);

    void setLevel(float level);

    void setFormat(AudioFormat format) override;

    float getTime() const noexcept;

    float getFeedback() const noexcept;

    float getLevel() const noexcept;

    AudioFormat getFormat() const noexcept override;

    void process(AudioBlock& block) override;

protected:
    float m_time;

    float m_feedback;

    float m_level;

    uint32_t m_delaySamples = 0;

    uint32_t m_maxDelaySamples = 0;

    std::vector<std::vector<float>> m_buffer;

    std::vector<uint32_t> m_writeIndex;
};
