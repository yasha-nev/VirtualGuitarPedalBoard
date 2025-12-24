#include "include/App.hpp"

#include <QDebug>

App::App(std::shared_ptr<Core> core, QObject* parent):
    QObject(parent),
    m_core(core) {
}

QStringList App::inputDeviceList() const {
    QStringList list;

    list.append("");

    for(const auto& d: m_core->getInputDeviceList()) {
        list.append(QString::fromUtf8(d.c_str()));
    }
    return list;
}

QStringList App::outputDeviceList() const {
    QStringList list;

    list.append("");

    for(const auto& d: m_core->getOutputDeviceList()) {
        list.append(QString::fromUtf8(d.c_str()));
    }

    return list;
}

void App::setInputDevice(QString device) {
    m_core->chooseInputDevice(device.toStdString());
}

void App::setOutputDevice(QString device) {
    m_core->chooseOutputDevice(device.toStdString());
}

void App::addPedal(UIBasePedal* pedal, int index) {
    if(!pedal) {
        return;
    }

    m_core->insertPedalByIndex(pedal->getPedal(), index);
}

void App::deletePedal(int index) {
    m_core->deletePedalByIndex(index);
}

void App::start() {
    m_core->start();
}

void App::stop() {
    m_core->stop();
}
