//MN Maker
//9.12.19

#include "HX711.h"

//OLED Display etup
#include <Wire.h>
#include <Math.h>
#include <ACROBOTIC_SSD1306_DORHEA.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels


// HX711 Load Cell Setup
const int LOADCELL_DOUT_PIN = 2;
const int LOADCELL_SCK_PIN = 3;

const int buttonPin = 4;     // the number of the pushbutton pin

// variables will change:
int buttonState = 0;         // variable for reading the pushbutton status

long current_Weight = 0;



HX711 scale;

void setup() {
  Serial.begin(38400);
  Wire.begin();
  oled.init();                      // Initialze SSD1306 OLED display

  // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT);

  delay(2000);  //Necessary delay for boot up
  oled.clearDisplay();

  //oled.setFont(font5x7);
  oled.setTextXY(0, 2);
  oled.putString("Initializing"); 
  oled.setTextXY(1, 5);
  oled.putString("Scale");


  delay(2500);
  oled.clearDisplay();

  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);

  scale.set_scale(111);                      // this value is obtained by calibrating the scale with known weights; see the README for details
  scale.tare();                // reset the scale to 0

}

void loop() {
  buttonState = digitalRead(buttonPin); // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
  if (buttonState == HIGH) {
    oled.clearDisplay();
    oled.setTextXY(0, 3);
    oled.putString("Calibrating"); 
    oled.setTextXY(1, 5);
    oled.putString("Scale");
    scale.tare();
    delay(500);
    oled.clearDisplay();
  }

  oled.setTextXY(1, 5);
  oled.putString("Weight:");
  
  
  //Get the Current Weight and Display it On the OLED
  current_Weight = scale.get_units(15);

  //current_Weight might be off by a factor of 4x 
  //Might check _scale via get_scale()
  
//  Serial.println("Weight: ");
//  Serial.println(current_Weight);

  //oled.setFont(font5x7);
  Serial.println(current_Weight);

  
  oled.setTextXY(3, 2);
  String str = "                                                    ";
  oled.putString(str);
  
      
  if(current_Weight > 999){
    oled.setTextXY(3, 3);
    oled.putNumber(current_Weight);
    oled.setTextXY(3, 8);
    oled.putString("grams");
  }
  else if(current_Weight > 99){
    oled.setTextXY(3, 4);
    oled.putNumber(current_Weight);
    oled.setTextXY(3, 8);
    oled.putString("grams");
  }
  else if(current_Weight > 9){
    oled.setTextXY(3, 5);
    oled.putNumber(current_Weight);
    oled.setTextXY(3, 8);
    oled.putString("grams");
  }
  else if(current_Weight < 0){
    if(current_Weight > -5){
      oled.setTextXY(3, 5);
      oled.putString("~0");
      oled.setTextXY(3, 8);
      oled.putString("grams");
    }
    else{
      oled.setTextXY(3, 2);
      oled.putString("Recalibration");
      oled.setTextXY(4, 3);
      oled.putString("Required");
    }
  }
  else{
    oled.setTextXY(3, 6);
    oled.putNumber(current_Weight);
    oled.setTextXY(3, 8);
    oled.putString("grams");
  }
  
  
  //scale.power_down();             // put the ADC in sleep mode
  delay(500);
  //scale.power_up();
}
