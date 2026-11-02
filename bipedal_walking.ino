#include <Servo.h>

// Create servo objects
Servo leftHipServo;
Servo rightHipServo;
Servo leftKneeServo;
Servo rightKneeServo;

// Pin assignments
const int LEFT_HIP_PIN = 2;
const int RIGHT_HIP_PIN = 3;
const int LEFT_KNEE_PIN = 4;
const int RIGHT_KNEE_PIN = 5;

// Neutral angles
const int NEUTRAL_LH = 90;
const int NEUTRAL_RH = 90;
const int NEUTRAL_LK = 90;
const int NEUTRAL_RK = 10;

// Walking parameters
const int HIP_SWING = 20;     // how much hips move
const int KNEE_LIFT = -60;     // how much knees bend
const int STEP_DELAY = 500;   // time between step phases

void setup() {
  leftHipServo.attach(LEFT_HIP_PIN);
  rightHipServo.attach(RIGHT_HIP_PIN);
  leftKneeServo.attach(LEFT_KNEE_PIN);
  rightKneeServo.attach(RIGHT_KNEE_PIN);

  // Set initial neutral pose
  setNeutralPose();

  delay(1000); // Wait before walking
}

void loop() {
  walkStep();
}

// Neutral standing position
void setNeutralPose() {
  leftHipServo.write(NEUTRAL_LH);
  rightHipServo.write(NEUTRAL_RH);
  leftKneeServo.write(NEUTRAL_LK);
  rightKneeServo.write(NEUTRAL_RK);
}

// One full step (left leg forward, then right leg forward)
void walkStep() {
  // === Step 1: Right Leg Forward ===
  // Bend LEFT knee (opposite) to shift weight
  leftKneeServo.write(NEUTRAL_LK + KNEE_LIFT);
  delay(200);
  // Swing right leg forward
  rightHipServo.write(NEUTRAL_RH - HIP_SWING);
  leftHipServo.write(NEUTRAL_LH + HIP_SWING);
  delay(STEP_DELAY);
  // Reset left knee
  leftKneeServo.write(NEUTRAL_LK);
  delay(100);

  // === Reset to Neutral ===
  setNeutralPose();
  delay(200);

  // === Step 2: Left Leg Forward ===
  // Bend RIGHT knee (opposite) to shift weight
  rightKneeServo.write(NEUTRAL_RK + KNEE_LIFT);
  delay(200);
  // Swing left leg forward
  leftHipServo.write(NEUTRAL_LH - HIP_SWING);
  rightHipServo.write(NEUTRAL_RH + HIP_SWING);
  delay(STEP_DELAY);
  // Reset right knee
  rightKneeServo.write(NEUTRAL_RK);
  delay(100);

  // === Reset to Neutral ===
  setNeutralPose();
  delay(200);
}
