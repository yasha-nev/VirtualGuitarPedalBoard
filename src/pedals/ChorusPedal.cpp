#include "ChorusPedal.hpp"

ChorusPedal::ChorusPedal() {
    m_type = PedalType::CHORUS;
}

void ChorusPedal::setFormat(AudioFormat format) {
    m_format = format;
}

AudioFormat ChorusPedal::getFormat() const noexcept {
    return m_format;
}

void ChorusPedal::process(AudioBlock& block) {
    (void) block;
}
