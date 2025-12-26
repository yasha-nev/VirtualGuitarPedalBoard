#include "ChorusPedal.hpp"

ChorusPedal::ChorusPedal(float rate, float depth):
    m_rate(rate),
    m_depth(depth) {
    m_type = PedalType::CHORUS;
}

void ChorusPedal::setFormat(AudioFormat format) {
    m_format = format;

    const uint32_t channels = format.channels;
    m_maxDelaySamples = static_cast<uint32_t>(format.sampleRate * 0.05f);

    m_buffer.resize(channels);
    m_writeIndex.resize(channels);

    for(uint32_t ch = 0; ch < channels; ++ch) {
        m_buffer[ch].assign(m_maxDelaySamples, 0.0f);
        m_writeIndex[ch] = 0;
    }

    m_phase = 0.0f;
}

void ChorusPedal::setRate(float rate) {
    m_rate = std::clamp(rate, 0.01f, 5.0f);
}

void ChorusPedal::setDepth(float depth) {
    m_depth = std::clamp(depth, 0.0f, 1.0f);
}

float ChorusPedal::getRate() const noexcept {
    return m_rate;
}

float ChorusPedal::getDepth() const noexcept {
    return m_depth;
}

AudioFormat ChorusPedal::getFormat() const noexcept {
    return m_format;
}

void ChorusPedal::process(AudioBlock& block) {
    const uint32_t frames = block.getFramesCount();
    const uint32_t channels = block.getFormat().channels;

    if(m_buffer.empty() || m_format.sampleRate != block.getFormat().sampleRate) {
        setFormat(block.getFormat());
    }

    constexpr float baseDelayMs = 8.0f;
    constexpr float maxDepthMs = 4.0f;
    constexpr float wetMix = 0.5f;

    const float phaseInc = 2.0f * static_cast<float>(M_PI) * m_rate / m_format.sampleRate;

    for(uint32_t f = 0; f < frames; ++f) {
        for(uint32_t ch = 0; ch < channels; ++ch) {
            float phaseOffset = (ch & 1) ? static_cast<float>(M_PI * 0.5f) : 0.0f;

            float lfo = std::sin(m_phase + phaseOffset);

            float delayMs = baseDelayMs + lfo * (1.0f + m_depth * maxDepthMs);

            float delaySamples = delayMs * m_format.sampleRate / 1000.0f;

            float delayed = readDelaySample(ch, delaySamples);

            uint32_t writeIndex = m_writeIndex[ch];
            float input = block.sample(ch, f);

            block.sample(ch, f) = input + delayed * wetMix;

            m_buffer[ch][writeIndex] = input;

            m_writeIndex[ch] = (writeIndex + 1) % m_maxDelaySamples;
        }

        m_phase += phaseInc;
        if(m_phase >= 2.0f * static_cast<float>(M_PI)) {
            m_phase -= 2.0f * static_cast<float>(M_PI);
        }
    }
}

float ChorusPedal::readDelaySample(uint32_t ch, float delaySamples) {
    auto& buffer = m_buffer[ch];
    uint32_t writeIndex = m_writeIndex[ch];

    float readPos = static_cast<float>(writeIndex) - delaySamples;
    if(readPos < 0.0f) {
        readPos += m_maxDelaySamples;
    }

    uint32_t i0 = static_cast<uint32_t>(readPos);
    uint32_t i1 = (i0 + 1) % m_maxDelaySamples;

    float frac = readPos - static_cast<float>(i0);

    return buffer[i0] * (1.0f - frac) + buffer[i1] * frac;
}
