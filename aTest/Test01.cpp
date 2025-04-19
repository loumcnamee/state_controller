#include <gtest/gtest.h>

#include "Controller.h"
#include "Event.h"
#include "State.h"
#include "HeatingState.h"


// Test state of controller once constructed
TEST(ControllerTests, ConstructorTest) {

  Controller<State, Event, Transitions> ctrl;
    
  ASSERT_EQ(ctrl.getStateName(),"Idle");
  
}

// Test controller state changes : State = Idle / Event = EventStop
TEST(ControllerTests, StateChangeTest01) {

  Controller<State, Event, Transitions> ctrl;
    
  ASSERT_EQ(ctrl.getStateName(),"Idle");

  ctrl.process(EventStop{});

  ASSERT_EQ(ctrl.getStateName(),"Idle");

  ctrl.process(EventTooCold{});

  ASSERT_EQ(ctrl.getStateName(),"Heating");
  
}

// Test controller state changes : State = Idle / Event = EventTooCold
TEST(ControllerTests, StateChangeTest02) {

  Controller<State, Event, Transitions> ctrl;
    
  ASSERT_EQ(ctrl.getStateName(),"Idle");

  ctrl.process(EventTooCold{});

  ASSERT_EQ(ctrl.getStateName(),"Heating");
  
}

// Test controller state changes : State = Idle / Event = EventTooHot
TEST(ControllerTests, StateChangeTest03) {

  Controller<State, Event, Transitions> ctrl;
    
  ASSERT_EQ(ctrl.getStateName(),"Idle");

  ctrl.process(EventTooHot{});

  ASSERT_EQ(ctrl.getStateName(),"Cooling");
  
}

// Test controller state changes : State = Heating / Event = EventStop
TEST(ControllerTests, StateChangeTest04) {

  Controller<State, Event, Transitions> ctrl;
    
  ASSERT_EQ(ctrl.getStateName(),"Idle");

  ctrl.process(EventTooCold{});

  ASSERT_EQ(ctrl.getStateName(),"Heating");

  ctrl.process(EventStop{});

  ASSERT_EQ(ctrl.getStateName(),"Idle");
  
}

// Test controller state changes : State = Heating / Event = EventStop
TEST(ControllerTests, StateChangeTest05) {

  Controller<State, Event, Transitions> ctrl;
    
  ASSERT_EQ(ctrl.getStateName(),"Idle");

  ctrl.process(EventTooHot{});

  ASSERT_EQ(ctrl.getStateName(),"Cooling");

  ctrl.process(EventStop{});

  ASSERT_EQ(ctrl.getStateName(),"Idle");
  
}

// Test controller temp model data
TEST(ControllerTests, TempDataTest) {

  Controller<State, Event, Transitions> ctrl;
    
  ASSERT_EQ(ctrl.getStateName(),"Idle");

  ASSERT_FLOAT_EQ(ctrl.getBuildingTemperature(), 22.0F);
  ASSERT_FLOAT_EQ(ctrl.getOutsideTemperature(), 0.0F);
  ASSERT_FLOAT_EQ(ctrl.getInputPower(), 0.0F);
  ASSERT_FLOAT_EQ(ctrl.getFloorArea(), 100.0F); 
  
}

// Test controller model to set outside temperature
TEST(ControllerTests, SetOusideTempTest) {

  const float insideTemp = 22.0F;
  const float initialOutsideTemp = 0.0F;
  const float powerOff = 0.0F;
  
  Controller<State, Event, Transitions> ctrl;
    
  ASSERT_EQ(ctrl.getStateName(),"Idle");
  
  ASSERT_EQ(ctrl.getOutsideTemperature(), initialOutsideTemp);
  
  const float outsideTemp = 101.5F;
  const float tempRange = 0.0F;
  ctrl.setOutsideTemperature(outsideTemp, tempRange);

  ASSERT_EQ(ctrl.getOutsideTemperature(), outsideTemp);
  
}

// Test controller to verify building cools when outside temp is less than outside temp and heater is off
TEST(ControllerTests, NaturalCoolingTest) {

  Controller<State, Event, Transitions> ctrl;
    
  ASSERT_EQ(ctrl.getStateName(),"Idle");
  ASSERT_EQ(ctrl.getBuildingTemperature(), 22.0F);
  ASSERT_EQ(ctrl.getOutsideTemperature(), 0.0F);
  ASSERT_EQ(ctrl.getInputPower(), 0.0F);

  //ctrl.process(EventTooCold{});

  //ASSERT_EQ(ctrl.getStateName(),"Heating");
  const float insideTemp = 22.0F;
  const float powerOff = 0.0F;
  ctrl.updateModel(1,timeOfDay(0.0F));
  ASSERT_EQ(ctrl.getStateName(),"Idle");
  ASSERT_LT(ctrl.getBuildingTemperature(), insideTemp);
  
  ASSERT_EQ(ctrl.getInputPower(), powerOff);
  
}

// Test controller verify building heats when outside temp is greater than outside temp and cooling is off
TEST(ControllerTests, NaturalHeatingTest) {

  const float insideTemp = 22.0F;
  const float powerOff = 0.0F;

  Controller<State, Event, Transitions> ctrl;
      
  ASSERT_EQ(ctrl.getStateName(),"Idle");
  ASSERT_FLOAT_EQ(ctrl.getBuildingTemperature(), insideTemp);
  ASSERT_FLOAT_EQ(ctrl.getOutsideTemperature(), 0.0F);
  ASSERT_FLOAT_EQ(ctrl.getInputPower(), powerOff);

  const float outsideTemp = 30.0F;
  const float tempRange = 0.0F;
  ctrl.setOutsideTemperature(outsideTemp, tempRange);
  
  ASSERT_FLOAT_EQ(ctrl.getOutsideTemperature(), outsideTemp);

  const float timeDelta = 60*60*12;
  const float midnight = 0.0F;
  ctrl.updateModel(timeDelta, timeOfDay(midnight));
  ASSERT_EQ(ctrl.getStateName(),"Idle");
  ASSERT_GT(ctrl.getBuildingTemperature(), 22.0F);
  
  ASSERT_FLOAT_EQ(ctrl.getInputPower(), 0.0F);

  
}

