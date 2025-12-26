#pragma once

#include "IBasePedal.hpp"

#include <QObject>

#include <memory>

class UIBasePedal: public QObject {
    Q_OBJECT

    Q_PROPERTY(bool isActive READ isActive NOTIFY isActiveChanged)

public:
    explicit UIBasePedal(QObject* parent = nullptr);

    bool isActive();

public slots:

    virtual void click();

    virtual std::shared_ptr<IBasePedal> getPedal();

signals:
    void isActiveChanged(bool active);

protected:
    std::shared_ptr<IBasePedal> m_pedal;
};
