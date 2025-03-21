#include "HomeHeatModel.h"

HomeHeatModel::HomeHeatModel() {

    input_power_ = 0.0;
    heat_mass_capacity_ = 2500.0f;
    building_temperature_ = 22.0f;
    outside_temperature_ = 0.0f;
    floor_area_ = 100.0f;
    
   
}







void HomeHeatModel::compute_temperature(float dt) 
{
     // ̂T 𝑖𝑛(𝑡)=𝑎[𝑇̂ 𝑖𝑛(𝑡−1)+Δ𝑡𝐶[𝑥1𝑃(𝑡−𝜃1)+𝑥2𝑃(𝑡−𝜃2)+𝑥3𝑃(𝑡−𝜃3)−𝑈[𝑇̂ 𝑖𝑛(𝑡−1)−𝑇𝑜𝑢𝑡(𝑡−1)]]]+𝑏

    // Model Paramters
    const float a = 1.0; //0.96;
    const float b = -273.0; //0.91;
    const float x1 = 0.15;
    const float x2 = 1.12;
    const float x3 = -0.85;
    const float U = 0.35; // Heat loss coefficient [kW/K] determione teh rate of heat exchange betweej inside and outside
    // P = heating power
    const float C = 0.1/60;  //heat capacity}
    float power_gain_= 50.0f;

    
    float old_temp = building_temperature_;

    //building_temperature_ = a*(old_temp + dt*C*(x1*input_power_ + x2*input_power_ + x3*input_power_ - U*(old_temp - outside_temperature_))) + b;
    building_temperature_ = a*((old_temp+273) + dt*C*(x1*input_power_ *power_gain_ - U*(old_temp - outside_temperature_)) ) + b;
    
    return;
}

void HomeHeatModel::setInputPower(float power)
 {
    input_power_ = power; 
    return;
}

void HomeHeatModel::setOutisdeTemperature(float temp)
{ 
    outside_temperature_ = temp; 
    return;
}

const float HomeHeatModel::getOutsideTemperature() const
{ 
    return outside_temperature_; 
}

const float HomeHeatModel::getBuildingTemperature() const
{ 
    return building_temperature_; 
}

const float HomeHeatModel::getInputPower() const
{ 
    return input_power_; 
}

const float HomeHeatModel::getFloorArea() const
{ 
    return floor_area_; 
}