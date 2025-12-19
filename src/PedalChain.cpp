#include "PedalChain.hpp"

PedalChain::PedalChain() {
}

void PedalChain::addPedal(std::unique_ptr<IBasePedal> pedal) {
    m_pedals.push_back(std::move(pedal));
}

void PedalChain::deletePedal(size_t index) {
    size_t i = 0;
    auto pedal = std::find_if(m_pedals.cbegin(), m_pedals.cend(), [&i, index](const auto& itr) {
        if(i == index) {
            return true;
        }

        i++;

        return false;
    });

    m_pedals.erase(pedal);
}

void PedalChain::process(AudioBlock& block) {
}
