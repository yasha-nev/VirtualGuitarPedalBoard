#include "PedalChain.hpp"

PedalChain::PedalChain():
    m_pedals(PEDALS_COUNT) {
}

void PedalChain::insertPedalByIndex(std::shared_ptr<IBasePedal> pedal, size_t index) {
    if(index >= m_pedals.size()) {
        return;
    }

    m_pedals[index] = std::move(pedal);
}

void PedalChain::deletePedalByIndex(size_t index) {
    if(index >= m_pedals.size()) {
        return;
    }

    m_pedals[index].reset();
}

void PedalChain::process(AudioBlock& block) {
    for(const auto& pedal: m_pedals) {
        if(!pedal || !pedal->isActive()) {
            continue;
        }

        pedal->process(block);
    }
}
