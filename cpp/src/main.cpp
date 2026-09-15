#include <iostream>
#include <array>
#include "../include/ai_runner/environment.hpp"

int main(){
    std::cout << "Physics environment booted. \n";

    ai_runner::Environment env;

    const auto initial_observation = env.reset();

    std::cout << "Initial position: " << initial_observation[0]<< "\n";
    std::cout << "Initial velocity: " << initial_observation[1]<< "\n";

    for(int i = 0; i < 10 ; ++i){
        const ai_runner::StepResult result = env.step(1.0F);

      
        std::cout << "Step " << i + 1
                  << " | position: " << result.observation[0]
                  << " | velocity: " << result.observation[1]
                  << " | reward: " << result.reward
                  << '\n';

        if ( result.terminated){
            std::cout << "Episode terminated after " << i + 1 << " steps.\n";
            break;
        }

    }


    return 0;
    

}
