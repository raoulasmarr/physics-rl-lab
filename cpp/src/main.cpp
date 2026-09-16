#include <iostream>
#include <array>
#include "../include/ai_runner/environment.hpp"
#include <mujoco/mujoco.h>


int main() {
    const std::string model_path =
        std::string(AI_RUNNER_ASSET_DIR) + "/models/humanoid/humanoid.xml";

    char error[1024] = "";

    mjModel* model = mj_loadXML(
        model_path.c_str(),
        nullptr,
        error,
        sizeof(error)
    );

    if (model == nullptr) {
        std::cerr << "Could not load model:\n" << error << '\n';
        return 1;
    }

    mjData* data = mj_makeData(model);

    std::cout << "Loaded: " << model_path << '\n';
    std::cout << "Position values (nq): " << model->nq << '\n';
    std::cout << "Velocity values (nv): " << model->nv << '\n';
    std::cout << "Actuator controls (nu): " << model->nu << '\n';

    mj_step(model, data);

    std::cout << "Simulation time after one step: "
              << data->time << " seconds\n";

    mj_deleteData(data);
    mj_deleteModel(model);

    return 0;
}
