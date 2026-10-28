#include <Servo.h> 

// Servo objects for dual-axis movement
Servo horizontalServo; 
Servo verticalServo;   

// Analog input pins connected to the 4 LDR voltage dividers
const int PIN_LDR_TL = A0; // 1st LDR: Top-Left
const int PIN_LDR_TR = A1; // 2nd LDR: Top-Right
const int PIN_LDR_BL = A2; // 3rd LDR: Bottom-Left
const int PIN_LDR_BR = A3; // 4th LDR: Bottom-Right

// Digital PWM pins for the 2 Servo motors
const int PIN_SERVO_H = 9;
const int PIN_SERVO_V = 10;

// SENSOR CALIBRATION & FEEDBACK CONTROL PARAMETERS
const int CAL_TL = 0;
const int CAL_TR = 0;
const int CAL_BL = 0;
const int CAL_BR = 0;

// Deadband threshold: stops movement when light intensity difference is within this value
const int THRESHOLD  = 15;  
const int STEP_SIZE  = 1;   
const int LOOP_DELAY = 30;  

// Safe mechanical rotation limits (in degrees)
const int MIN_ANGLE = 10;
const int MAX_ANGLE = 170;

// Current servo positions (initialized to 90° center position)
int angleH = 90;
int angleV = 90;

// Timer variable to prevent Serial Monitor lag in TinkerCAD
unsigned long lastPrintTime = 0;

void setup() {
  Serial.begin(9600);

  // Configure LDR pins as inputs
  pinMode(PIN_LDR_TL, INPUT);
  pinMode(PIN_LDR_TR, INPUT);
  pinMode(PIN_LDR_BL, INPUT);
  pinMode(PIN_LDR_BR, INPUT);

  // Attach servos and initialize to center (90 degrees)
  horizontalServo.attach(PIN_SERVO_H);
  verticalServo.attach(PIN_SERVO_V);
  
  horizontalServo.write(angleH);
  verticalServo.write(angleV);
  
  delay(500); // Allow servos to reach starting position
}

void loop() {
  // LIGHT DETECTION: Read and calibrate all 4 LDRs using analogRead()
  int tl = analogRead(PIN_LDR_TL) + CAL_TL;
  int tr = analogRead(PIN_LDR_TR) + CAL_TR;
  int bl = analogRead(PIN_LDR_BL) + CAL_BL;
  int br = analogRead(PIN_LDR_BR) + CAL_BR;

  // Compute directional light averages
  int avgTop   = (tl + tr) / 2;
  int avgBot   = (bl + br) / 2;
  int avgLeft  = (tl + bl) / 2;
  int avgRight = (tr + br) / 2;

  // Compute error (difference in light intensity across axes)
  int errorVert  = avgTop - avgBot;
  int errorHoriz = avgLeft - avgRight;

  // VERTICAL MOVEMENT & STABLE TRACKING
  if (abs(errorVert) > THRESHOLD) {
    int newAngleV = angleV;
    
    if (avgTop > avgBot) {
      newAngleV += STEP_SIZE; // Tilt up toward stronger top light
    } else {
      newAngleV -= STEP_SIZE; // Tilt down toward stronger bottom light
    }
    
    newAngleV = constrain(newAngleV, MIN_ANGLE, MAX_ANGLE);
    
    
    if (newAngleV != angleV) {
      angleV = newAngleV;
      verticalServo.write(angleV);
    }
  }

  // HORIZONTAL MOVEMENT & STABLE TRACKING
  if (abs(errorHoriz) > THRESHOLD) {
    int newAngleH = angleH;
    
    if (avgLeft > avgRight) {
      newAngleH -= STEP_SIZE; // Turn left toward stronger left light
    } else {
      newAngleH += STEP_SIZE; // Turn right toward stronger right light
    }
    
    newAngleH = constrain(newAngleH, MIN_ANGLE, MAX_ANGLE);
    
    // Only command servo if the angle actually changed
    if (newAngleH != angleH) {
      angleH = newAngleH;
      horizontalServo.write(angleH);
    }
  }

  // Throttled Serial output (updates every 300ms to prevent simulation lag)
  if (millis() - lastPrintTime >= 300) {
    lastPrintTime = millis();
    Serial.print("Top:"); Serial.print(avgTop);
    Serial.print(" Bot:"); Serial.print(avgBot);
    Serial.print(" Left:"); Serial.print(avgLeft);
    Serial.print(" Right:"); Serial.print(avgRight);
    Serial.print(" | Servo H:"); Serial.print(angleH);
    Serial.print("deg V:"); Serial.print(angleV);
    Serial.println("deg");
  }

  delay(LOOP_DELAY);
}
