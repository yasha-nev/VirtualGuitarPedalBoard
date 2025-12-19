#pragma once

#include "IBasePedal.hpp"

class DelayPedal: public IBasePedal {
public:
    DelayPedal();

    ~DelayPedal();

    void process(AudioBlock& block) override;

    void tongle() override;
};
