#pragma once

#include "DelayPedal.hpp"
#include "include/UIBasePedal.hpp"

class UIDelayPedal: public UIBasePedal {
    Q_OBJECT

    Q_PROPERTY(float time READ time WRITE setTime NOTIFY timeChanged FINAL)

    Q_PROPERTY(float feedback READ feedback WRITE setFeedback NOTIFY feedbackChanged FINAL)

    Q_PROPERTY(float level READ level WRITE setLevel NOTIFY levelChanged FINAL)

public:
    explicit UIDelayPedal(QObject* parent = nullptr);

    float time();

    float feedback();

    float level();

signals:

    void timeChanged(float);

    void feedbackChanged(float);

    void levelChanged(float);

public slots:

    void setTime(float time);

    void setFeedback(float feedback);

    void setLevel(float level);
};
