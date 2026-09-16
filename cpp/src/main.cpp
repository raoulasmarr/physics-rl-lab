#include "ai_runner/humanoid_environment.hpp"

#include <exception>
#include <iostream>
#include <string>

int main() {
    try {
        const std::string model_path =
            std::string(AI_RUNNER_ASSET_DIR) + "/models/humanoid/humanoid.xml";

        ai_runner::HumanoidEnvironment environment{model_path};

        const auto initial_observation = environment.reset();

        std::cout << "Observation size: "
                  << environment.observation_size() << '\n';

        std::cout << "Action size: "
                  << environment.action_size() << '\n';

        std::cout << "First observation value: "
                  << initial_observation[0] << '\n';

        return 0;
    } catch (const std::exception& error) {
        std::cerr << "Environment setup failed:\n"
                  << error.what() << '\n';

        return 1;
    }
}