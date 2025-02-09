#include <gtest/gtest.h>

#include "Controller.h"



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

  ASSERT_EQ(ctrl.getBuildingTemperature(), 22.0f);
  ASSERT_EQ(ctrl.getOutsideTemperature(), 10.0f);
  ASSERT_EQ(ctrl.getInputPower(), 0.0f);
  ASSERT_EQ(ctrl.getFloorArea(), 100.0f); 
     
  
}

// Test controller model to set outside temperature
TEST(ControllerTests, SetOusideTempTest) {

  Controller<State, Event, Transitions> ctrl;
    
  ASSERT_EQ(ctrl.getStateName(),"Idle");

  
  ASSERT_EQ(ctrl.getOutsideTemperature(), 10.0f);
  
  ctrl.setOutsideTemperature(101.5f);

  ASSERT_EQ(ctrl.getOutsideTemperature(), 101.5f);
     
  
}





// Test controller state changes : State = Heating / Event = EventStop
TEST(ControllerTests, HeatLoopTest) {

  Controller<State, Event, Transitions> ctrl;
    
  ASSERT_EQ(ctrl.getStateName(),"Idle");

  ctrl.process(EventTooCold{});

  ASSERT_EQ(ctrl.getStateName(),"Heating");
  
}

