#pragma once

#include "IBasePedal.hpp"

class ChorusPedal: public IBasePedal {
public:
    ChorusPedal();

    void process(AudioBlock& block) override;

    void setFormat(AudioFormat format) override;

    AudioFormat getFormat() const noexcept override;

    void tongle() override;
};
