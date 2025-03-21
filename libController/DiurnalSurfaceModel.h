#ifndef DIURANAL_SURFACE_TEMP_MODEL_H
#define DIURANAL_SURFACE_TEMP_MODEL_H


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

/** empirical model  */
class DiurnalSurfaceTemperatureModel
{

public:
    DiurnalSurfaceTemperatureModel();
    ~DiurnalSurfaceTemperatureModel() = default;
    
    
    float compute_surface_temperature(float tod, float daily_mean_temp, float daily_temp_range);
    
    

};

#endif