#include "ai_runner/humanoid_environment.hpp"

#include <exception>
#include <iostream>
#include <string>
#include <vector>

int main() {
    try {
        const std::string model_path =
            std::string(AI_RUNNER_ASSET_DIR) + "/models/humanoid/humanoid.xml";

        ai_runner::HumanoidEnvironment environment{model_path};

        const auto initial_observation = environment.reset();

        const std::vector<float> action(environment.action_size(), 0.0F);
        const auto step_result = environment.step(action);

        std::cout << "Reward after one zero-action step: "
          << step_result.reward << '\n';

        std::cout << "Episode ended: "
          << step_result.terminated << '\n';

        return 1;
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << '\n';
        return 1;
    }
}