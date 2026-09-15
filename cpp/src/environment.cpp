#include "ai_runner/environment.hpp"
#include <iostream>
#include <array>
#include <cmath>
#include <algorithm>

namespace ai_runner{

std::array<float,2> Environment::reset(){
    position_ = 0.0F;
    velocity_ = 0.0F;
    step_count_ = 0;

    return {position_, velocity_};
}

StepResult Environment::step(float action){
    constexpr float time_step = 0.02F;
    constexpr float max_action= 1.0F;
    constexpr float goal_position = 10.0F;
    constexpr int max_steps = 500;

    action = std::clamp(action , -max_action, max_action);

    velocity_ += action * time_step;
    position_ += velocity_ * time_step;
    ++step_count_;

    const bool reached_goal = position_ >= goal_position;
    const bool timed_out = step_count_ >= max_steps;

    StepResult result;
    result.observation = {position_, velocity_};
    result.reward = reached_goal ? 1.0F : -0.01F;
    result.terminated = reached_goal || timed_out;

    return result;
    

}
}