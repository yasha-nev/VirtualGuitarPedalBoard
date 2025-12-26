#include "include/UIChorusPedal.hpp"

UIChorusPedal::UIChorusPedal(QObject* parent):
    UIBasePedal(parent) {
    m_pedal = std::make_shared<ChorusPedal>();
}

float UIChorusPedal::depth() {
    ChorusPedal* pedal = static_cast<ChorusPedal*>(m_pedal.get());

    if(!pedal) {
        return 0.0f;
    }

    return pedal->getDepth();
}

float UIChorusPedal::rate() {
    ChorusPedal* pedal = static_cast<ChorusPedal*>(m_pedal.get());

    if(!pedal) {
        return 0.0f;
    }

    return pedal->getRate();
}

void UIChorusPedal::setDepth(float depth) {
    ChorusPedal* pedal = static_cast<ChorusPedal*>(m_pedal.get());

    depth = depth / 360;

    if(!pedal || pedal->getDepth() == depth) {
        return;
    }

    pedal->setDepth(depth);

    emit depthChanged(pedal->getDepth());
}

void UIChorusPedal::setRate(float rate) {
    ChorusPedal* pedal = static_cast<ChorusPedal*>(m_pedal.get());

    rate = rate / 72;

    if(!pedal || pedal->getRate() == rate) {
        return;
    }

    pedal->setDepth(rate);

    emit rateChanged(pedal->getRate());
}
