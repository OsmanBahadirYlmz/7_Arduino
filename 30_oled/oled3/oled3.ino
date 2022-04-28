
 
// Include Wire Library for I2C
#include <Wire.h>
 
// Include Adafruit Graphics & OLED libraries
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

 
// Reset pin not used but needed for library
#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);
 

 
void setup() {
  // Start Wire library for I2C
  Wire.begin();

  
  // initialize OLED with I2C addr 0x3C
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  
 
  // Clear the display
  display.clearDisplay();
  //Set the color - always use white despite actual display color
  display.setTextColor(WHITE);
  //Set the font size
  display.setTextSize(1);
  //Set the cursor coordinates
  display.setCursor(0,0);
  display.print("DroneBot Workshop");
  display.setCursor(0,10); 
  display.print("Humidity:    "); 

  display.print(" %");
  display.setCursor(0,20);
  display.print("Temperature: "); 

  display.print(" C");
}

void loop() {
 
  display.display();
  delay(100);
}
