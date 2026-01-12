#pragma once

#include <algorithm>
#include <atomic>
#include <cstddef>
#include <cstring>
#include <iostream>
#include <span>
#include <vector>

enum class SampleType {
    Float32,
};

typedef struct AudioFormat {
    uint32_t sampleRate;
    uint16_t channels;
    SampleType type;
    bool interleaved = false;
} AudioFormat;

size_t bytesPerSample(SampleType type) noexcept;

uint32_t frameSize(uint16_t channels, SampleType type) noexcept;

class AudioBlock {
public:
    AudioBlock(std::span<float> data, AudioFormat format, uint32_t framesCount):
        m_data(data),
        m_format(format),
        m_framesCount(framesCount) {
    }

    std::span<float>& getData() {
        return m_data;
    }

    uint32_t getFramesCount() {
        return m_framesCount;
    }

    AudioFormat getFormat() {
        return m_format;
    }

    float& sample(uint32_t ch, uint32_t frame) noexcept {
        if(m_format.interleaved) {
            return m_data[frame * m_format.channels + ch];
        }
        return m_data[ch * m_format.channels + frame];
    }

private:
    std::span<float> m_data;
    AudioFormat m_format;
    uint32_t m_framesCount;
};

class AudioRingBuffer {
public:
    AudioRingBuffer(AudioFormat format, uint32_t capacityFrames);

    bool push(AudioBlock& block);

    uint32_t pop(AudioBlock& block);

    void setFormat(AudioFormat format);

private:
    uint32_t availableFrames(uint32_t write, uint32_t read) const noexcept;

    uint32_t freeFrames(uint32_t write, uint32_t read) const noexcept;

    AudioFormat m_format;

    const uint32_t m_capacityFrames;

    std::vector<float> m_buffer;

    std::atomic<uint32_t> m_writeFrame { 0 };

    std::atomic<uint32_t> m_readFrame { 0 };
};
