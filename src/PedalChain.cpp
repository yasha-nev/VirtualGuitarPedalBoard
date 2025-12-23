#include "PedalChain.hpp"

PedalChain::PedalChain() {
}

void PedalChain::insertPedalByIndex(std::unique_ptr<IBasePedal> pedal, size_t index) {
    m_pedals.insert(m_pedals.cbegin() + index, std::move(pedal));
}

void PedalChain::deletePedalByIndex(size_t index) {
    m_pedals.erase(m_pedals.cbegin() + index);
}

void PedalChain::process(AudioBlock& block) {
    for(const auto& pedal: m_pedals) {
        if(pedal->isActive()) {
            pedal->process(block);
        }
    }
}
