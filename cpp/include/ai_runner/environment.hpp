#pragma once

#include <array>

namespace ai_runner{
    
struct StepResult{
    std::array<float, 2> observation;

    float reward;
    bool terminated;
};

class Environment{

public: 
    std::array<float, 2> reset();
    StepResult step(float action);

private:
    float position_ = 0.0F;
    float velocity_ = 0.0F;
    int step_count_ = 0;
};






}