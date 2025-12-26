#pragma once

#include "ChorusPedal.hpp"
#include "include/UIBasePedal.hpp"

class UIChorusPedal: public UIBasePedal {
    Q_OBJECT

    Q_PROPERTY(float depth READ depth WRITE setDepth NOTIFY depthChanged FINAL)

    Q_PROPERTY(float rate READ rate WRITE setRate NOTIFY rateChanged FINAL)

public:
    explicit UIChorusPedal(QObject* parent = nullptr);

    float depth();

    float rate();

signals:

    void depthChanged(float);

    void rateChanged(float);

public slots:

    void setDepth(float depth);

    void setRate(float rate);
};
