#pragma once

#include <mujoco/mujoco.h>
#include <string>
#include <vector>

namespace ai_runner {

class HumanoidEnvironment {
public:
    explicit HumanoidEnvironment(const std::string& model_path);
    ~HumanoidEnvironment();

    HumanoidEnvironment(const HumanoidEnvironment&) = delete;
    HumanoidEnvironment& operator=(const HumanoidEnvironment&) = delete;

    std::vector<float> reset();

    int  observation_size() const;
    int  action_size() const;

private:
    mjModel* model_ = nullptr;
    mjData* data_ = nullptr;

    std::vector<float> observation() const;


};
// namespace ai_runner
}