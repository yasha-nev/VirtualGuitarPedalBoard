#pragma once

#include "AudioBuffer.hpp"
#include "IBasePedal.hpp"

#include <list>
#include <vector>

class PedalChain {
public:
    PedalChain();

    void addPedal(std::unique_ptr<IBasePedal> pedal);

    void deletePedal(size_t index);

    void process(AudioBlock& block);

private:
    std::list<std::unique_ptr<IBasePedal>> m_pedals;
};
