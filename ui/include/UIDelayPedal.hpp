#pragma once

#include "DelayPedal.hpp"
#include "include/UIBasePedal.hpp"

class UIDelayPedal: public UIBasePedal {
    Q_OBJECT

    Q_PROPERTY(float time READ getTime WRITE setTime NOTIFY timeChanged FINAL)

    Q_PROPERTY(float feedback READ getFeedback WRITE setFeedback NOTIFY feedbackChanged FINAL)

    Q_PROPERTY(float level READ getLevel WRITE setLevel NOTIFY levelChanged FINAL)

public:
    explicit UIDelayPedal(QObject* parent = nullptr);

    float getTime();

    float getFeedback();

    float getLevel();

signals:

    void timeChanged(float);

    void feedbackChanged(float);

    void levelChanged(float);

public slots:

    std::shared_ptr<IBasePedal> getPedal() override;

    void setTime(float time);

    void setFeedback(float feedback);

    void setLevel(float level);
};
