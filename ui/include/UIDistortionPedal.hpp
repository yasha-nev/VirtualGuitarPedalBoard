#pragma once

#include "DistortionPedal.hpp"
#include "include/UIBasePedal.hpp"

class UIDistortionPedal: public UIBasePedal {
    Q_OBJECT

    Q_PROPERTY(float tone READ getTone WRITE setTone NOTIFY toneChanged FINAL)

    Q_PROPERTY(float dist READ getDist WRITE setDist NOTIFY distChanged FINAL)

    Q_PROPERTY(float level READ getLevel WRITE setLevel NOTIFY levelChanged FINAL)

public:
    explicit UIDistortionPedal(QObject* parent = nullptr);

    float getTone();

    float getDist();

    float getLevel();

signals:

    void toneChanged(float);

    void distChanged(float);

    void levelChanged(float);

public slots:

    std::shared_ptr<IBasePedal> getPedal() override;

    void setTone(float tone);

    void setDist(float dist);

    void setLevel(float level);
};
