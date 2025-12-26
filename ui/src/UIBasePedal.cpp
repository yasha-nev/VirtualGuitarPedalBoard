#include "include/UIBasePedal.hpp"

UIBasePedal::UIBasePedal(QObject* parent):
    QObject(parent),
    m_pedal(nullptr) {
}

bool UIBasePedal::isActive() {
    if(!m_pedal) {
        return false;
    }

    return m_pedal->isActive();
}

std::shared_ptr<IBasePedal> UIBasePedal::getPedal() {
    return m_pedal;
}

void UIBasePedal::click() {
    if(!m_pedal) {
        return;
    }

    m_pedal->tongle();

    emit isActiveChanged(m_pedal->isActive());
}
