#include "HomeHeatModel.h"

#include "constants.h"

HomeHeatModel::HomeHeatModel() : input_power_{model_defaults::initialInputPower},
                                 heat_mass_capacity_{model_defaults::initialHeatMassCapacity},
                                 building_temperature_{model_defaults::initialBuildingTemperature},
                                 outside_temperature_{model_defaults::initial_daily_mean_temp},
                                 floor_area_{model_defaults::initialFloorArea}
{
    // Default constructor   
}







void HomeHeatModel::compute_temperature(float timeSpanSeconds) 
{
     // ̂T 𝑖𝑛(𝑡)=𝑎[𝑇̂ 𝑖𝑛(𝑡−1)+Δ𝑡𝐶[𝑥1𝑃(𝑡−𝜃1)+𝑥2𝑃(𝑡−𝜃2)+𝑥3𝑃(𝑡−𝜃3)−𝑈[𝑇̂ 𝑖𝑛(𝑡−1)−𝑇𝑜𝑢𝑡(𝑡−1)]]]+𝑏

    // Model Paramters
    constexpr float coeff_a = 1.0; //0.96;
    constexpr float coeff_b = -273.0; //0.91;
    constexpr float coeff_x1 = 0.15;
    //const float x2 = 1.12;
    //const float x3 = -0.85;
    constexpr float heat_loss_coeff = 0.35; // Heat loss coefficient [kW/K] determione teh rate of heat exchange betweej inside and outside
    // P = heating power
    constexpr float heat_capacity = 0.1/60.0F;  //heat capacity}
    constexpr float power_gain_= 50.0F;  // 50W/m2
    
    float old_temp = building_temperature_;

    //building_temperature_ = coeff_a*(old_temp + dt*heat_capacity*(coeff_x1*input_power_ + x2*input_power_ + x3*input_power_ - heat_loss_coeff*(old_temp - outside_temperature_))) + coeff_b;
    building_temperature_ = coeff_a*((old_temp-physical_constants::absolute_zero) + timeSpanSeconds*heat_capacity*(coeff_x1*input_power_ *power_gain_ - heat_loss_coeff*(old_temp - outside_temperature_)) ) + coeff_b;
    
}

void HomeHeatModel::setInputPower(float power)
{
    input_power_ = power; 
    
}

void HomeHeatModel::setOutisdeTemperature(float temp)
{ 
    outside_temperature_ = temp; 
    
}

float HomeHeatModel::getOutsideTemperature() const
{ 
    return outside_temperature_; 
}

float HomeHeatModel::getBuildingTemperature() const
{ 
    return building_temperature_; 
}

float HomeHeatModel::getInputPower() const
{ 
    return input_power_; 
}

float HomeHeatModel::getFloorArea() const
{ 
    return floor_area_; 
}