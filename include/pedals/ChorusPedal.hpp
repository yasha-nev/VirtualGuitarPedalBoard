#pragma once

#include "IBasePedal.hpp"

class ChorusPedal: public IBasePedal {
public:
    ChorusPedal();

    ~ChorusPedal();

    void process(AudioBlock& block) override;

    void tongle() override;
};
