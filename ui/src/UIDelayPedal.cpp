#include "include/UIDelayPedal.hpp"

UIDelayPedal::UIDelayPedal(QObject* parent):
    UIBasePedal(parent) {
    m_pedal = std::make_shared<DelayPedal>();
}

std::shared_ptr<IBasePedal> UIDelayPedal::getPedal() {
    return m_pedal;
}

float UIDelayPedal::getTime() {
    DelayPedal* pedal = static_cast<DelayPedal*>(m_pedal.get());

    return pedal->getTime();
}

float UIDelayPedal::getFeedback() {
    DelayPedal* pedal = static_cast<DelayPedal*>(m_pedal.get());

    return pedal->getFeedback();
}

float UIDelayPedal::getLevel() {
    DelayPedal* pedal = static_cast<DelayPedal*>(m_pedal.get());

    return pedal->getLevel();
}

void UIDelayPedal::setTime(float time) {
    DelayPedal* pedal = static_cast<DelayPedal*>(m_pedal.get());

    time = time / 180;

    if(pedal->getTime() == time) {
        return;
    }

    pedal->setTime(time);

    emit timeChanged(pedal->getTime());
}

void UIDelayPedal::setFeedback(float feedback) {
    DelayPedal* pedal = static_cast<DelayPedal*>(m_pedal.get());

    feedback = feedback / 360;

    if(pedal->getFeedback() == feedback) {
        return;
    }

    pedal->setFeedback(feedback);

    emit feedbackChanged(pedal->getFeedback());
}

void UIDelayPedal::setLevel(float level) {
    DelayPedal* pedal = static_cast<DelayPedal*>(m_pedal.get());

    level = level / 360;

    if(pedal->getLevel() == level) {
        return;
    }

    pedal->setLevel(level);

    emit levelChanged(pedal->getLevel());
}
