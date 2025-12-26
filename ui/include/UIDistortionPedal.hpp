#pragma once

#include "DistortionPedal.hpp"
#include "include/UIBasePedal.hpp"

class UIDistortionPedal: public UIBasePedal {
    Q_OBJECT

    Q_PROPERTY(float tone READ tone WRITE setTone NOTIFY toneChanged FINAL)

    Q_PROPERTY(float dist READ dist WRITE setDist NOTIFY distChanged FINAL)

    Q_PROPERTY(float level READ level WRITE setLevel NOTIFY levelChanged FINAL)

public:
    explicit UIDistortionPedal(QObject* parent = nullptr);

    float tone();

    float dist();

    float level();

signals:

    void toneChanged(float);

    void distChanged(float);

    void levelChanged(float);

public slots:

    void setTone(float tone);

    void setDist(float dist);

    void setLevel(float level);
};
