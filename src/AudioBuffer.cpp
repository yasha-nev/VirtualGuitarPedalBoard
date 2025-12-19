#include "AudioBuffer.hpp"

size_t bytesPerSample(SampleType type) noexcept {
    switch(type) {
        case SampleType::Float32:
            return sizeof(float);
    }
    return 0;
}

uint32_t frameSize(uint16_t channels, SampleType type) noexcept {
    return channels * bytesPerSample(type);
}

AudioRingBuffer::AudioRingBuffer(AudioFormat format, uint32_t capacityFrames):
    m_format(format),
    m_capacityFrames(capacityFrames),
    m_buffer(capacityFrames * frameSize(m_format.channels, m_format.type)) {
}

uint32_t AudioRingBuffer::availableFrames(uint32_t write, uint32_t read) const noexcept {
    return write - read;
}

uint32_t AudioRingBuffer::freeFrames(uint32_t write, uint32_t read) const noexcept {
    return m_capacityFrames - availableFrames(write, read);
}

#include <iostream>

bool AudioRingBuffer::push(AudioBlock& block) {
    AudioFormat format = block.getFormat();
    std::span<float>& input = block.getData();
    uint32_t framesCount = block.getFramesCount();

    const uint32_t fsize = frameSize(format.channels, format.type);
    const uint32_t bytes = framesCount * fsize;

    if(input.size_bytes() < bytes) {
        return false;
    }

    const uint32_t write = m_writeFrame.load(std::memory_order_relaxed);
    const uint32_t read = m_readFrame.load(std::memory_order_acquire);

    if(freeFrames(write, read) < framesCount) {
        return false;
    }

    const uint32_t writeIndex = write % m_capacityFrames;
    const uint32_t firstPart = std::min(framesCount, m_capacityFrames - writeIndex);

    std::memcpy(m_buffer.data() + writeIndex * fsize, input.data(), firstPart * fsize);

    if(firstPart < framesCount) {
        std::memcpy(
            m_buffer.data(), input.data() + firstPart * fsize, (framesCount - firstPart) * fsize);
    }

    m_writeFrame.store(write + framesCount, std::memory_order_release);

    return true;
}

uint32_t AudioRingBuffer::pop(AudioBlock& block) {
    AudioFormat format = block.getFormat();
    std::span<float>& output = block.getData();
    uint32_t maxFrames = block.getFramesCount();

    const uint32_t fsize = frameSize(format.channels, format.type);

    const uint32_t write = m_writeFrame.load(std::memory_order_acquire);
    const uint32_t read = m_readFrame.load(std::memory_order_relaxed);

    const uint32_t available = availableFrames(write, read);
    const uint32_t frames = std::min(available, maxFrames);
    const uint32_t bytes = frames * fsize;

    if(frames == 0 || output.size_bytes() < bytes) {
        return 0;
    }

    const uint32_t readIndex = read % m_capacityFrames;
    const uint32_t firstPart = std::min(frames, m_capacityFrames - readIndex);

    std::memcpy(output.data(), m_buffer.data() + readIndex * fsize, firstPart * fsize);

    if(firstPart < frames) {
        std::memcpy(
            output.data() + firstPart * fsize, m_buffer.data(), (frames - firstPart) * fsize);
    }

    m_readFrame.store(read + frames, std::memory_order_release);

    return frames;
}

void AudioRingBuffer::setFormat(AudioFormat format) {
    m_format = format;

    m_buffer.resize(m_capacityFrames * frameSize(m_format.channels, m_format.type));
}
