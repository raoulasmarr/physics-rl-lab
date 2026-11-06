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
        auto step_result = environment.step(action);

        for (int i = 0; i < 100; ++i) {
            step_result = environment.step(action);

            std::cout << "Step " << i + 1
                    << " | Reward: " << step_result.reward
                    << '\n';

            if (step_result.terminated) {
                std::cout << "Episode terminated at step: " << i + 1 << '\n';
                break;
            }
        }
        std::cout << "Reward after 100 steps: "
          << step_result.reward << '\n';

        std::cout << "Episode ended: "
          << step_result.terminated << '\n';

        return 0;
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << '\n';
        return 1;
    }
}