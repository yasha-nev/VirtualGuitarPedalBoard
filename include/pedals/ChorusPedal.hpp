#pragma once

#include "IBasePedal.hpp"

class ChorusPedal: public IBasePedal {
public:
    explicit ChorusPedal(float rate = 0.0f, float depth = 0.0f);

    void setRate(float rate);

    void setDepth(float depth);

    void setFormat(AudioFormat format) override;

    float getRate() const noexcept;

    float getDepth() const noexcept;

    AudioFormat getFormat() const noexcept override;

    void process(AudioBlock& block) override;

private:
    float readDelaySample(uint32_t ch, float delaySamples);

    float m_rate;

    float m_depth;

    float m_phase = 0.0f;

    uint32_t m_maxDelaySamples = 0;

    std::vector<std::vector<float>> m_buffer;

    std::vector<uint32_t> m_writeIndex;
};
