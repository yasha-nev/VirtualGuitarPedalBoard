#pragma once

#include "Core.hpp"
#include "include/UIBasePedal.hpp"

#include <QObject>
#include <QStringList>
#include <QThread>

#include <memory>

class App: public QObject {
    Q_OBJECT;

    Q_PROPERTY(QStringList inputDeviceList READ inputDeviceList NOTIFY inputDeviceListChanged)

    Q_PROPERTY(QStringList outputDeviceList READ outputDeviceList NOTIFY outputDeviceListChanged)

public:
    explicit App(std::shared_ptr<Core> core, QObject* parent = nullptr);

public slots:

    QStringList inputDeviceList() const;

    QStringList outputDeviceList() const;

    void setInputDevice(QString deviceIndex);

    void setOutputDevice(QString deviceIndex);

    void start();

    void stop();

    void addPedal(UIBasePedal* pedal, int index);

    void deletePedal(int index);

signals:
    void inputDeviceListChanged();
    void outputDeviceListChanged();

private:
    std::shared_ptr<Core> m_core;
};
