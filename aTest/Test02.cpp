#include <gtest/gtest.h>
#include "DiurnalSurfaceModel.h"

class DiurnalSurfaceTemperatureModelTest : public ::testing::Test {
protected:
    DiurnalSurfaceTemperatureModel model;

    void SetUp() override {
        // Default test setup
        model.setTimeOfDayHours(12.0F);
        model.setLatitude(45.0F);
        model.setDayOfYear(182);
    }
};

TEST_F(DiurnalSurfaceTemperatureModelTest, DefaultConstructor) {
    DiurnalSurfaceTemperatureModel defaultModel;
    EXPECT_DOUBLE_EQ(0.0, defaultModel.getTimeOfDayHours());
    EXPECT_DOUBLE_EQ(0.0, defaultModel.getLatitude());
    EXPECT_EQ(1, defaultModel.getDayOfYear());
}

TEST_F(DiurnalSurfaceTemperatureModelTest, SettersAndGetters) {
    DiurnalSurfaceTemperatureModel model;
    const float expectedTimeOfDay = 6.0F;
    const float expectedLatitude = 30.0F;
    const int expectedDayOfYear = 90;
    model.setTimeOfDayHours(expectedTimeOfDay);
    model.setLatitude(expectedLatitude);
    model.setDayOfYear(expectedDayOfYear);

    EXPECT_DOUBLE_EQ(6.0F, model.getTimeOfDayHours());
    EXPECT_DOUBLE_EQ(30.0F, model.getLatitude());
    EXPECT_EQ(90, model.getDayOfYear());
}

TEST_F(DiurnalSurfaceTemperatureModelTest, TemperatureAtNoon) {
    // Test temperature calculation at noon
    model.setTimeOfDayHours(12.0);
    model.setLatitude(0.0); // At equator
    model.setDayOfYear(182); // Around July 1st

    model.setOutsideTemperature(10.0f,10.0f);
    double temp = model.compute_surface_temperature(12.0f);
    EXPECT_GT(temp, 0.0); // Temperature should be positive
    EXPECT_LT(temp, 50.0); // Temperature should be reasonable
}

TEST_F(DiurnalSurfaceTemperatureModelTest, TemperatureAtMidnight) {
    model.setTimeOfDayHours(0.0);
    model.setLatitude(0.0);
    model.setDayOfYear(182);

    model.setOutsideTemperature(-10.0f,5.0f);
    double temp = model.compute_surface_temperature(0.0f);
    EXPECT_GT(temp, -20.0); // Night temperature should be above extreme cold
    EXPECT_LT(temp, 30.0);  // Night temperature should be below day temperature
}

TEST_F(DiurnalSurfaceTemperatureModelTest, InvalidInputs) {
    // Test time of day validation
    // expect time of day to wrap for positive values greter than 24
    model.setTimeOfDayHours(24.5f);
    EXPECT_DOUBLE_EQ(0.5f, model.getTimeOfDayHours());

    // expect time of day to throw for negative values
    EXPECT_THROW(model.setTimeOfDayHours(-20.0), std::invalid_argument);
    

    // Test latitude validation
    EXPECT_THROW(model.setLatitude(91.0), std::invalid_argument);
    EXPECT_THROW(model.setLatitude(-91.0), std::invalid_argument);

    // Test day of year validation
    EXPECT_THROW(model.setDayOfYear(0), std::invalid_argument);

    model.setDayOfYear(367);
    EXPECT_DOUBLE_EQ(2, model.getDayOfYear());
    EXPECT_THROW(model.setDayOfYear(-1), std::invalid_argument);
}
