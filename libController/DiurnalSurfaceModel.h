#ifndef DIURANAL_SURFACE_TEMP_MODEL_H
#define DIURANAL_SURFACE_TEMP_MODEL_H

#include <cmath>


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
private:
    float daily_mean_temp ;
    float daily_temp_range;    
    float time_of_day; // Time of day in hours
    float latitude; // Latitude in degrees
    int day_of_year; // Day of the year (1-365)
    
    // Constants
    const float STEFAN_BOLTZMANN_CONSTANT = 5.67e-8; // W/m^2/K^4
    const float SOLAR_CONSTANT = 1367; // W/m^2

    // Helper functions
    float calculate_solar_radiation(float latitude, int day_of_year);
    float calculate_day_length(float latitude, int day_of_year);

public:
    DiurnalSurfaceTemperatureModel();
    ~DiurnalSurfaceTemperatureModel() = default;

    // Accessors
    float getTimeOfDayHours() const { return time_of_day; }
    float getLatitude() const { return latitude; }
    int getDayOfYear() const { return day_of_year; }
    
    void setDayOfYear(int day);
    
    /**
    * @brief Sets the time of day and ensures it's within 24-hour range
    * @param time_of_day Time in hours (0-24)
    * @return adjusted time of day within 24-hour range
    */
    void setTimeOfDayHours(float tod);

    void setOutsideTemperature(float meanTeamp, float tempRange);

    /**
    * @brief Sets the latitude value and ensures it's within valid range (-90 to 90 degrees)
    * @param lat Latitude in degrees
    * @return adjusted latitude value clamped to valid range
    */
    void setLatitude(float lat);

    float compute_surface_temperature(float tod);
};

#endif