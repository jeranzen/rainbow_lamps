// NeoPixel Ring simple sketch (c) 2013 Shae Erisson
// Released under the GPLv3 license to match the rest of the
// Adafruit NeoPixel library

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
 #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

// Which pin on the Arduino is connected to the NeoPixels?
#define PIN        3 // On Trinket or Gemma, suggest changing this to 1
#define knob      A0

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS 24 // Popular NeoPixel ring size

// When setting up the NeoPixel library, we tell it how many pixels,
// and which pin to use to send signals. Note that for older NeoPixel
// strips you might need to change the third parameter -- see the
// strandtest example for more information on possible values.
Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

#define DELAYVAL 100 // Time (in milliseconds) to pause between pixels

void setup() {
  Serial.begin(9600);
  pinMode(A0, INPUT);
  pixels.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)
}

void loop() {
  //pixels.clear(); // Set all pixel colors to 'off'

  // The first NeoPixel in a strand is #0, second is 1, all the way up
  // to the count of pixels minus one.
  for(int i=0; i<NUMPIXELS; i++) { // For each pixel...

    // pixels.Color() takes RGB values, from 0,0,0 up to 255,255,255
    // Here we're using a moderately bright green color:
    
    colorSelect(i);
    pixels.show();   // Send the updated pixel colors to the hardware.

    delay(DELAYVAL); // Pause before next pass through loop
    
  }
}


/*
 * TY to Ontaelio on instructibles for the rainbow colour generator code in the colorSelect() function
 * https://www.instructables.com/How-to-Make-Proper-Rainbow-and-Random-Colors-With-/
 */
void colorSelect(int pixel){

byte red, green, blue;

int knobVal = analogRead(knob);

int angle = map(knobVal, 0, 1023, 0, 360);

  if (angle<60) {red = 255; green = round(angle*4.25-0.01); blue = 0;} else
  if (angle<120) {red = round((120-angle)*4.25-0.01); green = 255; blue = 0;} else 
  if (angle<180) {red = 0, green = 255; blue = round((angle-120)*4.25-0.01);} else 
  if (angle<240) {red = 0, green = round((240-angle)*4.25-0.01); blue = 255;} else 
  if (angle<300) {red = round((angle-240)*4.25-0.01), green = 0; blue = 255;} else 
                 {red = 255, green = 0; blue = round((360-angle)*4.25-0.01);} 

  
  pixels.setPixelColor(pixel, pixels.Color(red, green, blue));


  return;
}
