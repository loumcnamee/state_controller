// libController/constants.h
#ifndef CONSTANTS_H
#define CONSTANTS_H


// Physical and related constants used in the models and application
namespace physical_constants {
    constexpr float  hoursPerDay = 24.0F;
    constexpr float  secondsPerHour = 3600.0F;
    constexpr float maxLatitude = 90.0F;
    constexpr float minLatitude = -90.0F;
    constexpr int maxDayOfYear = 365.0F;
    constexpr int minDayOfYear = 1.0F;

    constexpr float STEFAN_BOLTZMANN_CONSTANT = 5.67e-8; // W/m^2/K^4
    constexpr float SOLAR_CONSTANT = 1367; // W/m^2

    constexpr float absolute_zero = -273.15F; // Celsius
 
  
} // namespace physical_constants

// Constants used for the model defaults
namespace model_defaults {
    constexpr float initialBuildingTemperature = 22.0F; // Initial building temperature in Celsius
    constexpr float initialOutsideTemperature = 0.0F; // Initial outside temperature in Celsius
    constexpr float initialInputPower = 0.0F; // Initial input power in Watts
    constexpr float defaultPower = 1.0F; // default power for heating and cooling in Watts
    constexpr float initialFloorArea = 100.0F; // Initial floor area in square meters

    constexpr float initialHeatMassCapacity = 1000.0F; // Initial heat mass capacity in J/K
    constexpr float initialHeatTransmission = 10.0F; // Initial heat transmission in W/K
    constexpr float initialMaxCoolingPower = -1000.0F; // Initial maximum cooling power in Watts
    constexpr float initialMaxHeatingPower = 1000.0F; // Initial maximum heating power in Watts

    constexpr float initial_time_of_day = 0.0F; // Default time of day,
    constexpr float initial_latitude = 0.0F; // Default latitude
    constexpr int initial_day_of_year = 1; // Default day of the year
    constexpr float initial_daily_mean_temp = 10.0F; // Default mean temperature;
    constexpr float initial_daily_temp_range = 10.0F; // Default temperature range
} // namespace model_defaults

#endif