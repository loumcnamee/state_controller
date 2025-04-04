# State Controller Design Document

## Overview
This application simulates thermal control of a simple building using the libController library and Qt framework. It provides a single-window interface for monitoring and controlling building temperature states.

## Components

### User Interface
- Single Qt window implementation
- Real-time temperature display
- Control input widgets
- Status indicators

### Controller Integration
- libController integration for thermal simulation
- State management system
- Temperature control algorithms

## Architecture
```mermaid
graph TD
    A[Qt UI] --> B[State Manager]
    B --> C[libController]
    C --> D[Thermal Simulation]
    D --> B
```
## State Machine
The state machine diagram illustrates the interaction control flow and state transitions between different user-system interactions.

![State machine diagram](state_machine.drawio.svg)

This diagram shows:
- Transition states between different user actions
- Control flow of the system interaction
- Event triggers and state changes
- Entry and exit conditions for each state

## Models
This application uses two models to simulate heating and cooling of the interior of a structure given outside temperature
- the class HomeHeatModel simulates the effect of HVAC plan output on interior temperature

- the class DiurnalSurfaceTemperatureModel simulates the exterior surface air termperature as a function of time of day, latitude and day of year
Source: Hietaharju, P.; Ruusunen, M.; Leiviskä, K. A Dynamic Model for Indoor Temperature Prediction in Buildings. Energies 2018, 11, 1477. https://doi.org/10.3390/en11061477

## User Interface
![User Interface Design](ux.drawio.svg)

The interface layout shows the main components and their arrangement within the application window. Temperature controls and status indicators are positioned for optimal user interaction.

## Key Features
- Real-time temperature monitoring
- Manual control overrides
- Automated temperature regulation
- State persistence
- Error handling and alerts

## Sequence Diagram
```mermaid
sequenceDiagram
    participant UI as MainWindow
    participant SM as StateManager
    participant HC as HomeController
    participant HM as HomeHeatModel
    participant DM as DiurnalModel

    UI->>UI: setupUi()
    UI->>SM: create()
    SM->>HC: initialize()
    HC->>HM: create()
    HC->>DM: create()
    
    activate SM
    SM->>HC: startSimulation()
    activate HC
    
    loop Every Timer Tick
        HC->>DM: getExternalTemp()
        DM-->>HC: temperature
        HC->>HM: updateTemp(external)
        HM-->>HC: internalTemp
        HC-->>SM: stateUpdate
        SM-->>UI: updateDisplay
    end
    
    deactivate HC
    deactivate SM
```