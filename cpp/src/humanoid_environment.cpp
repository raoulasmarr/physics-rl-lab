#include "ai_runner/humanoid_environment.hpp"
#include <stdexcept>

namespace ai_runner {

HumanoidEnvironment::HumanoidEnvironment(const std::string& model_path) {//loads the humanoid model from the specified path and initializes the model and data members
    char error[1024] = "";

    model_ = mj_loadXML(model_path.c_str(), nullptr, error, sizeof(error));

    if (model_ == nullptr) {
        throw std::runtime_error("Could not load model: " + std::string(error));
    }
    torso_body_id_ = mj_name2id(model_, mjOBJ_BODY, "torso");

    if (torso_body_id_ == -1) {
        mj_deleteModel(model_);
        model_ = nullptr;
        throw std::runtime_error("Could not find the torso body.");
    }

    data_ = mj_makeData(model_);

    if (data_ == nullptr){
        mj_deleteModel(model_);
        model_ = nullptr;
        throw std::runtime_error(
            std::string("Could not load humanoid model:\n") + error
        );
    }

}

HumanoidEnvironment::~HumanoidEnvironment() {
   mj_deleteData(data_);
   mj_deleteModel(model_);
}
std::vector<float> HumanoidEnvironment::reset() {
    mj_resetData(model_, data_);
    mj_forward(model_, data_);

    return observation();
}

int HumanoidEnvironment::observation_size() const {
    return model_->nq + model_->nv;
}

int HumanoidEnvironment::action_size() const {
    return model_->nu;
}

std::vector<float> HumanoidEnvironment::observation() const {
    std::vector<float> result;
    result.reserve(observation_size());

    for (int index = 0; index < model_->nq; ++index) {
        result.push_back(static_cast<float>(data_->qpos[index]));
    }

    for (int index = 0; index < model_->nv; ++index) {
        result.push_back(static_cast<float>(data_->qvel[index]));
    }

    return result;
}
HumanoidStepResult HumanoidEnvironment::step(const std::vector<float>& action){
    if(action_size() != static_cast<int>(action.size())){
        throw std::invalid_argument("Action must contain exactly " + std::to_string(action_size()) + " elements.");
    }

    for(int index = 0 ; index< action_size(); ++index){
        data_->ctrl[index] = action[index];

    }

    mj_step(model_, data_);

    const float torso_height = static_cast<float>(
        data_->xpos[3 * torso_body_id_ + 2]
    );

    HumanoidStepResult result;
    result.observation = observation();
    result.reward = torso_height;
    result.terminated = torso_height < 0.75F || data_->time >= 5.0;

    return result;
}

} // namespace ai_runner

