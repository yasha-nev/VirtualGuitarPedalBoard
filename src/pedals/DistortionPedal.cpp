#include "DistortionPedal.hpp"

DistortionPedal::DistortionPedal(float dist, float tone, float level):
    m_tone(tone),
    m_dist(dist),
    m_level(level) {
    m_active = false;
    m_type = PedalType::DISTORTION;
}

DistortionPedal::~DistortionPedal() {
}

void DistortionPedal::setDist(float dist) {
    m_dist = dist;
}

void DistortionPedal::setTone(float tone) {
    m_tone = tone;
}

void DistortionPedal::setLevel(float level) {
    m_level = level;
}

float DistortionPedal::getDist() const noexcept {
    return m_dist;
}

float DistortionPedal::getTone() const noexcept {
    return m_tone;
}

float DistortionPedal::getLevel() const noexcept {
    return m_level;
}

float DistortionPedal::preFilter(float x, float last) {
    // RC high/low simplified
    return 0.995f * x + 0.005f * last;
}

float DistortionPedal::clip(float x) {
    const float threshold = 0.44f;
    if(x > threshold) {
        return threshold;
    }
    if(x < -threshold) {
        return -threshold;
    }
    return x;
}

float DistortionPedal::toneFilter(float x, float last) {
    float alpha = m_tone * 0.8f + 0.2f;
    return alpha * x + (1.0f - alpha) * last;
}

void DistortionPedal::process(AudioBlock& block) {
    const uint32_t frames = block.getFramesCount();
    const uint32_t channels = block.getFormat().channels;

    for(uint32_t ch = 0; ch < channels; ++ch) {
        float lastSamplePre = m_lastSamplePre[ch];
        float lastSampleTone = m_lastSampleTone[ch];

        for(uint32_t f = 0; f < frames; ++f) {
            float x = block.sample(ch, f);

            x = preFilter(x, lastSamplePre);
            lastSamplePre = x;

            float gain = 1.0f + m_dist * 24.0f;
            x *= gain;

            x = clip(x);

            x = toneFilter(x, lastSampleTone);
            lastSampleTone = x;

            x *= m_level;

            block.sample(ch, f) = x;
        }

        m_lastSamplePre[ch] = lastSamplePre;
        m_lastSampleTone[ch] = lastSampleTone;
    }
}

void DistortionPedal::tongle() {
    m_active = !m_active;
}
