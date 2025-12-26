#include "include/UIDistortionPedal.hpp"

UIDistortionPedal::UIDistortionPedal(QObject* parent):
    UIBasePedal(parent) {
    m_pedal = std::make_shared<DistortionPedal>();
}

float UIDistortionPedal::tone() {
    DistortionPedal* pedal = static_cast<DistortionPedal*>(m_pedal.get());

    if(!pedal) {
        return 0.0f;
    }

    return pedal->getTone();
}

float UIDistortionPedal::dist() {
    DistortionPedal* pedal = static_cast<DistortionPedal*>(m_pedal.get());

    if(!pedal) {
        return 0.0f;
    }

    return pedal->getDist();
}

float UIDistortionPedal::level() {
    DistortionPedal* pedal = static_cast<DistortionPedal*>(m_pedal.get());

    if(!pedal) {
        return 0.0f;
    }

    return pedal->getLevel();
}

void UIDistortionPedal::setTone(float tone) {
    DistortionPedal* pedal = static_cast<DistortionPedal*>(m_pedal.get());

    tone = tone / 360;

    if(!pedal || pedal->getTone() == tone) {
        return;
    }

    pedal->setTone(tone);

    emit toneChanged(pedal->getTone());
}

void UIDistortionPedal::setDist(float dist) {
    DistortionPedal* pedal = static_cast<DistortionPedal*>(m_pedal.get());

    dist = dist / 360;

    if(!pedal || pedal->getDist() == dist) {
        return;
    }

    pedal->setDist(dist);

    emit distChanged(pedal->getDist());
}

void UIDistortionPedal::setLevel(float level) {
    DistortionPedal* pedal = static_cast<DistortionPedal*>(m_pedal.get());

    level = level / 360;

    if(!pedal || pedal->getLevel() == level) {
        return;
    }

    pedal->setLevel(level);

    emit levelChanged(pedal->getLevel());
}
