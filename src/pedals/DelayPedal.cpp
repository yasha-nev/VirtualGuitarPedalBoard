#include "DelayPedal.hpp"

DelayPedal::DelayPedal(float time, float feedback, float level):
    m_time(time),
    m_feedback(feedback),
    m_level(level) {
    m_type = PedalType::DELAY;
}

void DelayPedal::setTime(float time) {
    m_time = std::clamp(time, 0.0f, 2.0f);
    m_delaySamples = static_cast<uint32_t>(m_time * m_format.sampleRate);
}

void DelayPedal::setFeedback(float feedback) {
    m_feedback = std::clamp(feedback, 0.0f, 0.95f);
}

void DelayPedal::setLevel(float level) {
    m_level = std::clamp(level, 0.0f, 1.0f);
}

void DelayPedal::setFormat(AudioFormat format) {
    m_format = format;

    size_t channels = format.channels;
    m_maxDelaySamples = format.sampleRate * 2;

    m_buffer.resize(channels);
    m_writeIndex.resize(channels);

    for(uint32_t ch = 0; ch < channels; ++ch) {
        m_buffer[ch].assign(m_maxDelaySamples, 0.0f);
        m_writeIndex[ch] = 0;
    }
}

float DelayPedal::getTime() const noexcept {
    return m_time;
}

float DelayPedal::getFeedback() const noexcept {
    return m_feedback;
}

float DelayPedal::getLevel() const noexcept {
    return m_level;
}

AudioFormat DelayPedal::getFormat() const noexcept {
    return m_format;
}

void DelayPedal::process(AudioBlock& block) {
    const uint32_t frames = block.getFramesCount();
    const uint32_t channels = block.getFormat().channels;

    if(m_buffer.empty() || m_format.sampleRate != block.getFormat().sampleRate) {
        setFormat(block.getFormat());
    }

    for(uint32_t ch = 0; ch < channels; ++ch) {
        auto& buffer = m_buffer[ch];
        uint32_t writeIndex = m_writeIndex[ch];

        for(uint32_t f = 0; f < frames; ++f) {
            float input = block.sample(ch, f);

            uint32_t readIndex = (writeIndex + m_maxDelaySamples - m_delaySamples) %
                m_maxDelaySamples;

            float delayed = buffer[readIndex];

            buffer[writeIndex] = input + delayed * m_feedback;

            writeIndex = (writeIndex + 1) % m_maxDelaySamples;

            float output = input + delayed * m_level;

            block.sample(ch, f) = output;
        }

        m_writeIndex[ch] = writeIndex;
    }
}
