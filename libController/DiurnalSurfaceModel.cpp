#include "DiurnalSurfaceModel.h"
#include <system_error>
#include <cmath>


DiurnalSurfaceTemperatureModel::DiurnalSurfaceTemperatureModel() {
    time_of_day = 0.0f; // Default time of day
    latitude = 0.0f; // Default latitude
    day_of_year = 1; // Default day of the year
     daily_mean_temp = 10.0f;
     daily_temp_range = 10.0f;
   
}


void DiurnalSurfaceTemperatureModel::setTimeOfDayHours(float tod) {
    if (tod < 0) {
        throw std::invalid_argument("Time of day cannot be negative");
    }
    // Ensure time stays within 24-hour range using modulo 
    time_of_day = fmod(tod, 24.0f);
    return;
}

void DiurnalSurfaceTemperatureModel::setOutsideTemperature(float meanTemp, float tempRange) {\

    daily_mean_temp = meanTemp;
    daily_temp_range = tempRange;
    return;
}


void DiurnalSurfaceTemperatureModel::setLatitude(float lat) {
    if (lat < -90.0f || lat > 90.0f) {
        throw std::invalid_argument("Latitude must be between -90 and 90 degrees");
    }
    latitude = std::max(-90.0f, std::min(90.0f, lat));
    return;
}

void DiurnalSurfaceTemperatureModel::setDayOfYear(int day) {
    if (day <= 0) {
        throw std::invalid_argument("Day must be a positive integer");
    }
    
    day_of_year = (day % 365);
    return;
}

float DiurnalSurfaceTemperatureModel::compute_surface_temperature(float tod)
{
     
    // ̂Temp(t) = = A0 +A1*X1 + a1*X2*COS(pi*tod/12)+b1*SIN(pi*tod/12)+a2*X2*COS(pi*tod/6)+b2*X2*SIN(pi*tod/6)
    // Determining the Diurnal Variation of Surface Temperature in Mountainous Terrain by Morris H. McCutchan
    // Print Publication: 01 Sep 1979
    // DOI: https://doi.org/10.1175/1520-0450(1979)018<1224:DTDVOS>2.0.CO;2

    // Model Paramters
    const float A0	= -0.32815;
    const float A1	= 0.96592;
    const float a1	= -0.43502;
    const float b1	= -0.14453;
    const float a2	= 0.09995;
    const float b2	= 0.0245;

    const float pi = 3.14159265359;
    
    
    float surface_temp = A0 + A1*daily_mean_temp + a1*daily_temp_range*cos(pi*tod/12)+ b1*daily_temp_range*sin(pi*tod/12) + a2*daily_temp_range*cos(pi*tod/6) + b2*daily_temp_range*sin(pi*tod/6);
        
    
    return surface_temp;
}

