# Smart Solar Panel

Smart Solar Panel is an Arduino-based dual-axis solar tracking system designed to orient a solar panel toward the brightest light source. It uses four Light Dependent Resistors (LDRs) to detect differences in light intensity and two servo motors to adjust the panel's horizontal and vertical positions.

The Arduino continuously compares the readings from the four sensors and moves the servos toward the brighter direction. This helps the panel maintain better alignment with the incoming sunlight compared to a fixed-position panel so that the solar panel always receives the most amount of energy through sunlight.

## Mechanism

The four LDRs are arranged in a 2 × 2 pattern to measure light intensity from different directions. The Arduino compares the average readings from the top, bottom, left and right sensors. When the difference exceeds a threshold of 15, the corresponding servo moves by 1° toward the brighter side. A deadband threshold helps prevent unnecessary movements caused by small fluctuations in light intensity.

## Components Used
- Arduino UNO
- Four Light Dependent Resistors (LDRs)
- Two micro servo motors
- Four resistors for LDR voltage dividers
- Breadboard and jumper wires
- Tinkercad Circuits for simulation

## Future Applications

1. **Solar power plants:** Could be adapted for tracking systems that help solar panels follow the Sun throughout the day.
2. **Solar-powered devices:** Could improve the orientation of small solar-powered garden lights, chargers and remote monitoring stations.
3. **Renewable energy research:** Can serve as a learning platform for experimenting with solar tracking, sensor calibration and automated control systems.
