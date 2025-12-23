#pragma once

#include "AudioBuffer.hpp"
#include "IBasePedal.hpp"

#include <vector>

class PedalChain {
public:
    PedalChain();

    void insertPedalByIndex(std::unique_ptr<IBasePedal> pedal, size_t index);

    void deletePedalByIndex(size_t index);

    void process(AudioBlock& block);

private:
    std::vector<std::unique_ptr<IBasePedal>> m_pedals;
};
