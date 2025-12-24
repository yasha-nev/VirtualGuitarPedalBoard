#include "PedalChain.hpp"

PedalChain::PedalChain() {
    m_pedals.resize(5);

    for(auto& pedal: m_pedals) {
        pedal = nullptr;
    }
}

void PedalChain::insertPedalByIndex(std::shared_ptr<IBasePedal> pedal, size_t index) {
    m_pedals.insert(m_pedals.cbegin() + index, pedal);
}

void PedalChain::deletePedalByIndex(size_t index) {
    m_pedals.erase(m_pedals.cbegin() + index);
}

void PedalChain::process(AudioBlock& block) {
    for(const auto& pedal: m_pedals) {
        if(pedal && pedal->isActive()) {
            pedal->process(block);
        }
    }
}
