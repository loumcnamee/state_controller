#include "DiurnalSurfaceModel.h"

#include <cmath>


DiurnalSurfaceTemperatureModel::DiurnalSurfaceTemperatureModel() {
    
   
}


float DiurnalSurfaceTemperatureModel::compute_surface_temperature(float tod, float daily_mean_temp, float daily_temp_range)
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

