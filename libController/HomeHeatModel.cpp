#include "HomeHeatModel.h"

HomeHeatModel::HomeHeatModel() {

    input_power_ = 0.0;
    heat_mass_capacity_ = 100.0f;
    building_temperature_ = 22.0f;
    outside_temperature_ = 10.0f;
    floor_area_ = 100.0f;
    
}

void HomeHeatModel::compute_temperature(float dt) 
{
    const float His = 3.45; // W/(m*m*K)
    float heat_transmission = His*floor_area_;
    float old_temp = building_temperature_;
    building_temperature_ = old_temp* (1 - dt / heat_mass_capacity_ * heat_transmission) + dt / heat_mass_capacity_ * (input_power_ + heat_transmission*outside_temperature_ );   
    
    return;
}