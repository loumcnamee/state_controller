#ifndef HOME_HEAT_MODEL_H
#define HOME_HEAT_MODEL_H

// θm,t = θm,t-1 × (1 - Δt / Cm × Htr, em) + Δt / Cm × (ΦHC, nd, t-1 + Htr, em × θe, t-1)
// ΦHC, nd, t: cooling or heating power at time t
// State Variables
// θm, t: building temperature [℃] at time t
// Parameters
// θe, t: outside temperature [℃] at time t
// Af: conditioned floor area [m2]
// Cm: capacity of the building's heat mass [J/K]
// Δt: time step size [s]
// Htr, em: heat transmission to the outside [W/K]
// θint, C, set: cooling set point temperature [℃]
// θint, H, set: heating set point temperature [℃]
// ΦC, max: maximum cooling power [W]
// ΦH, max: maximum heating power [W]
/**
   Parameters:
        * heat_mass_capacity:           capacity of the building's heat mass [J/K]
        * heat_transmission:            heat transmission to the outside [W/K]
        * maximum_cooling_power:        [W] (<= 0)
        * maximum_heating_power:        [W] (>= 0)
        * initial_building_temperature: building temperature at start time [℃]
        * time_step_size:               [s]
        * conditioned_floor_area:       [m**2]
        * 
*/

class HomeHeatModel
{
private:
    float input_power_;
    float heat_mass_capacity_;
    float building_temperature_;
    float outside_temperature_;
    float floor_area_;

public:
    HomeHeatModel();
    HomeHeatModel(float heat_mass_capacity, float heat_transmission, float maximum_cooling_power, float maximum_heating_power, float initial_building_temperature, float time_step_size, float conditioned_floor_area);
    ~HomeHeatModel() = default;
    void compute_temperature(float dt);
    void setOutisdeTemperature(float temp);
    const float getOutsideTemperature() const;
    const float getBuildingTemperature() const;
    const float getInputPower() const;
    const float getFloorArea() const;
    void setInputPower(float power);
    

};

#endif