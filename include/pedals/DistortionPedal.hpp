#pragma once

#include "IBasePedal.hpp"

class DistortionPedal: public IBasePedal {
public:
    DistortionPedal();

    ~DistortionPedal();

    void process(AudioBlock& block) override;

    void tongle() override;
};
