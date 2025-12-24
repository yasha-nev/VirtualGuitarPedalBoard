#include "include/UIDistortionPedal.hpp"

UIDistortionPedal::UIDistortionPedal(QObject* parent):
    UIBasePedal(parent) {
    m_pedal = std::make_shared<DistortionPedal>();
}

std::shared_ptr<IBasePedal> UIDistortionPedal::getPedal() {
    return m_pedal;
}

float UIDistortionPedal::getTone() {
    DistortionPedal* pedal = static_cast<DistortionPedal*>(m_pedal.get());

    return pedal->getTone();
}

float UIDistortionPedal::getDist() {
    DistortionPedal* pedal = static_cast<DistortionPedal*>(m_pedal.get());

    return pedal->getDist();
}

float UIDistortionPedal::getLevel() {
    DistortionPedal* pedal = static_cast<DistortionPedal*>(m_pedal.get());

    return pedal->getLevel();
}

void UIDistortionPedal::setTone(float tone) {
    DistortionPedal* pedal = static_cast<DistortionPedal*>(m_pedal.get());

    if(pedal->getTone() == tone) {
        return;
    }

    pedal->setTone(tone / 360);

    emit toneChanged(pedal->getTone());
}

void UIDistortionPedal::setDist(float dist) {
    DistortionPedal* pedal = static_cast<DistortionPedal*>(m_pedal.get());

    if(pedal->getDist() == dist) {
        return;
    }

    pedal->setDist(dist / 360);

    emit distChanged(pedal->getDist());
}

void UIDistortionPedal::setLevel(float level) {
    DistortionPedal* pedal = static_cast<DistortionPedal*>(m_pedal.get());

    if(pedal->getLevel() == level) {
        return;
    }

    pedal->setLevel(level / 360);

    emit levelChanged(pedal->getLevel());
}
