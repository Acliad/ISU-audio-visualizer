#include <Adafruit_NeoPixel.h>

#define PIN 20
#define START_MARKER 254
#define END_MARKER 255

const int ledCount = 250;

// Flag to track when it's time to update the LED strip
boolean frameReady = false;
// Track if in the middle of getting components
boolean pixelReady = false;
// One byte for each of the 3 color components
byte rgbData[3];
// Track the pixel we're updating
byte pixelNumber = 0;

// For debugging
int timeToColor = 0;

// Set up the LED strip
Adafruit_NeoPixel strip = Adafruit_NeoPixel(ledCount, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  // Start the UART
  Serial1.begin(115200);

  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
}

void loop() {

  // For calculating the time spent durring a loop
  unsigned long startTime = millis();


  for (int i = 0; i < ledCount; i++) {
    // Holds the color for this pixel
    unsigned long color = 0;
    // For each color
    for (int j = 0; j < 3; j++) {
      // Assembly each 8 bit component (R,G,B) in to a single 32bit number
      while (!Serial1.available()) {
        // Wait until there is data in the serial buffer
      }

      // Get the color component for this pixel, set the first 8 bits of the 24 bit color,
      // then shift those over to make room for the next 8
      color = (color | (Serial1.read() << 8 * j));
    }

    // Calculate the ammount of time it took to get all the color components
    timeToColor = millis() - startTime;

    // Now that we have the color for this pixel, update it in the buffer
    strip.setPixelColor(i, color);
  }

  // Update all the LEDS
  strip.show();

  // Print null character so Pi knows shifting is done
  Serial1.println('\0');
  delay(500);
}

void getPixelData() {
  // This function gets the color for a single pixel,
  // one component at a time.

  static byte index = 0; // Index for RGB component array

  if(Serial.available() > 0) {
    // If there is Serial data in the buffer
    byte recievedData = Serial.read();

    switch (recievedData){
      case START_MARKER:
        // Set up conditions to start recieving a pixel color
        index = 0;
        pixelNumber = 0;
        pixelReady = false;
        frameReady = false;
        break;
      case END_MARKER:
        // Done recieving the pixels' colors, ready to proccess
        frameReady = true;
        break;
      default:
        if(!pixelReady) {
          // Add recieved data to buffer
          rgbData[index] = recievedData;
          index++;
        }
        if(index == 2) {
          // When we have all 3 components, set a pixel
          setPixel();
          index = 0;
          pixelReady = false;
        }
        break;
  }
  }
}

void setPixel() {
  strip.setPixelColor(pixelNumber, rgbData[0], rgbData[1], rgbData[2]);
  pixelNumber++;
}

void updateFrame() {
  // Proccess buffer and update LEDS
}
