#pragma once

#include <mujoco/mujoco.h>
#include <string>
#include <vector>

namespace ai_runner {

struct HumanoidStepResult {
    std::vector<float> observation;
    float reward;
    bool terminated;
};

class HumanoidEnvironment {
public:
    explicit HumanoidEnvironment(const std::string& model_path);
    ~HumanoidEnvironment();

    HumanoidEnvironment(const HumanoidEnvironment&) = delete;
    HumanoidEnvironment& operator=(const HumanoidEnvironment&) = delete;

    std::vector<float> reset();
    HumanoidStepResult step(const std::vector<float>& action);

    int  observation_size() const;
    int  action_size() const;

private:
    mjModel* model_ = nullptr;
    mjData* data_ = nullptr;
    int torso_body_id_ = -1;

    std::vector<float> observation() const;


};
// namespace ai_runner
}