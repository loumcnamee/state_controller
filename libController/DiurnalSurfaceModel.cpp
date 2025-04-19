#include "DiurnalSurfaceModel.h"
#include <system_error>
#include <cmath>
#include "constants.h"


DiurnalSurfaceTemperatureModel::DiurnalSurfaceTemperatureModel() :  time_of_day{model_defaults::initial_time_of_day}, // Default time of day,
                                                                    day_of_year{model_defaults::initial_day_of_year}, // Default day of the year                                                                    
                                                                    latitude{model_defaults::initial_latitude}, // Default latitude
                                                                    daily_mean_temp{model_defaults::initial_daily_mean_temp}, // Default mean temperature;
                                                                    daily_temp_range{model_defaults::initial_daily_temp_range}, // Default temperature range
                                                                    outside_temp{model_defaults::initial_daily_mean_temp} // Outside temperature in Celsius

{
   
}


void DiurnalSurfaceTemperatureModel::setTimeOfDayHours(float tod) {
    if (tod < 0) {
        throw std::invalid_argument("Time of day cannot be negative");
    }
    // Ensure time stays within 24-hour range using modulo 
    time_of_day = fmodf(tod, physical_constants::hoursPerDay);

}

void DiurnalSurfaceTemperatureModel::setOutsideTemperature(float meanTemp, float tempRange) {

    daily_mean_temp = meanTemp;
    daily_temp_range = tempRange;

}


void DiurnalSurfaceTemperatureModel::setLatitude(float lat) {
    if (lat < physical_constants::minLatitude || lat > physical_constants::maxLatitude) {
        throw std::invalid_argument("Latitude must be between -90 and 90 degrees");
    }
    latitude = std::max(physical_constants::minLatitude, std::min(physical_constants::maxLatitude, lat));
    
}

void DiurnalSurfaceTemperatureModel::setDayOfYear(int day) {
    if (day <= 0) {
        throw std::invalid_argument("Day must be a positive integer");
    }
    
    day_of_year = (day % physical_constants::maxDayOfYear) + 1; // Ensure day is within 1-365 range
    
}

float DiurnalSurfaceTemperatureModel::compute_surface_temperature(float tod) const
{
     
    // ̂Temp(t) = = A0 +A1*X1 + a1*X2*COS(pi*tod/12)+b1*SIN(pi*tod/12)+a2*X2*COS(pi*tod/6)+b2*X2*SIN(pi*tod/6)
    // Determining the Diurnal Variation of Surface Temperature in Mountainous Terrain by Morris H. McCutchan
    // Print Publication: 01 Sep 1979
    // DOI: https://doi.org/10.1175/1520-0450(1979)018<1224:DTDVOS>2.0.CO;2

    // Model Paramters which are Fourier series coefficients
    constexpr float coeff_A0	= -0.32815F;
    constexpr float coeff_A1	= 0.96592F;
    constexpr float coeff_a1	= -0.43502F;
    constexpr float coeff_b1	= -0.14453F;
    constexpr float coeff_a2	= 0.09995F;
    constexpr float coeff_b2	= 0.0245F;

    constexpr int freq_12 = physical_constants::hoursPerDay/2; // 12 hours
    constexpr int freq_6 = physical_constants::hoursPerDay/4; // 6 hours
       
    float surface_temp = coeff_A0 + (coeff_A1*daily_mean_temp) + (coeff_a1*daily_temp_range*cosf(M_PI*tod/freq_12)) + (coeff_b1*daily_temp_range*sinf(M_PI*tod/freq_12)) + (coeff_a2*daily_temp_range*cosf(M_PI*tod/freq_6)) + (coeff_b2*daily_temp_range*sinf(M_PI*tod/freq_6));
        
    
    return surface_temp;
}

