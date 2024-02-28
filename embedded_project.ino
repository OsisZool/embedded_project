#include <PS2X_lib.h>
#include <Wire.h>


#define PS2_CLK   9   // CLK
#define PS2_CS    10  // CS
#define PS2_CMD   11  // CMD
#define PS2_DAT   12  // DAT

PS2X ps2x; // Create PS2X Controller Object

int motor_LF = A0; // output motor left front
int motor_LB = A1; // output motor left back
int motor_RF = A2;
int motor_RB = A3;

// ขวา
int in_a = 2;
int in_b = 3;
int pwm = 5;

// ซ้าย 
int in_c = 6;
int in_d = 7;

bool start_psb = false;
bool has_printed_start_control = false;
bool has_pink_pressed = false;

void car_direction(int F,B){
  digitalWrite(in_a, F);
  digitalWrite(in_b, B);
  digitalWrite(in_c, F);
  digitalWrite(in_d, B);
}

void setup() {
  Serial.begin(9600);
  
  // Initialize PS2 Controller
  ps2x.config_gamepad(PS2_CLK, PS2_CMD, PS2_CS, PS2_DAT, false, false);
  pinMode(motor_LF, OUTPUT);
  pinMode(motor_LB, OUTPUT);
  pinMode(motor_RF, OUTPUT);
  pinMode(motor_RB, OUTPUT);
  pinMode(in_a, OUTPUT);
  pinMode(in_b, OUTPUT);
  pinMode(in_c, OUTPUT);
  pinMode(in_d, OUTPUT);
  pinMode(pwm, OUTPUT);
  
  // Check for error
  int error = ps2x.readType();
  if(error == 1) {
    Serial.println("Found DualShock Controller");
  } else {
    Serial.println("No controller found or error");
  }
}

void loop() {

  int spped = 50;
  // analogWrite(pwm,speed);
  // Read PS2 controller data
  ps2x.read_gamepad();
  
  // Check if PSB_START is pressed
  if(ps2x.ButtonPressed(PSB_START)){
    start_psb = !start_psb;
    Serial.print(start_psb);
    
    // If Start control is activated
      if(start_psb) {
        if (!has_printed_start_control) {
          Serial.println("Start control");
          has_printed_start_control = true;

        }
      } else {
        has_printed_start_control = false;
        Serial.println("Stop !!!");
      }
    } 
  if (has_printed_start_control == true){
      
      //Set Button ตรงนี้จ้า
      if(ps2x.ButtonPressed(PSB_R1)){
      Serial.println("R1");
      }
      else if(ps2x.ButtonPressed(PSB_PAD_UP)){
        Serial.println("UP");
        analogWrite(pwm, 100);
        car_direction(0,1);
        delay(50);
        

      }
      else if(ps2x.ButtonPressed(PSB_PAD_RIGHT)){
      Serial.println("Right");
      }
      else if(ps2x.ButtonPressed(PSB_PAD_DOWN)){
        Serial.println("Down");
        analogWrite(pwm, 100);
        car_direction(1,0);
        delay(50);
      }
      else if(ps2x.ButtonPressed(PSB_PAD_LEFT)){
        Serial.println("Left");
      }
      else if(ps2x.ButtonPressed(PSB_PINK)){
        Serial.println("Pink");
        has_pink_pressed = true;
        if(has_pink_pressed){
          if(ps2x.ButtonPressed(PSB_GREEN)){
            Serial.println("Green");
          }
        }
      }
      else if(ps2x.ButtonPressed(PSB_BLUE)){
        Serial.println("Blue");
      }
      else if(ps2x.ButtonPressed(PSB_RED)){
        Serial.println("Red");
        analogWrite(pwm, 100);
        car_direction(0,0);
        delay(50);
      }
  }
  
  delay(50); // Delay for stability
}


  
  // Print button states
  // Serial.print("Triangle: "); Serial.print(ps2x.Button(PSB_TRIANGLE));
  // Serial.print("  Circle: "); Serial.print(ps2x.Button(PSB_CIRCLE));
  // Serial.print("  Cross: "); Serial.print(ps2x.Button(PSB_CROSS));
  // Serial.print("  Square: "); Serial.print(ps2x.Button(PSB_SQUARE));
  // Serial.print("  L1: "); Serial.print(ps2x.Button(PSB_L1));
  // Serial.print("  L2: "); Serial.print(ps2x.Button(PSB_L2));
  // Serial.print("  R1: "); Serial.print(ps2x.Button(PSB_R1));
  // Serial.print("  R2: "); Serial.println(ps2x.Button(PSB_R2));
  
  // Serial.print("  R2: "); Serial.println(ps2x.Button(PSB_PAD_UP));
  
