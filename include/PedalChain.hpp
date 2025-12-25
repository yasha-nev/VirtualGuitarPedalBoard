#pragma once

#include "AudioBuffer.hpp"
#include "IBasePedal.hpp"

#include <vector>

#define PEDALS_COUNT 5

class PedalChain {
public:
    PedalChain();

    void insertPedalByIndex(std::shared_ptr<IBasePedal> pedal, size_t index);

    void deletePedalByIndex(size_t index);

    void process(AudioBlock& block);

private:
    std::vector<std::shared_ptr<IBasePedal>> m_pedals;
};
