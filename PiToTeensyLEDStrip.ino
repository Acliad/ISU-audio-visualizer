#include <Adafruit_NeoPixel.h>

#define PIN 20
#define START_MARKER 254
#define END_MARKER 255

const int ledCount = 250;
// For debugging
int timeToColor = 0;
boolean frameReady = false;
byte rgbData[ledCount];

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

void getFrame() {
  // This function gets the color
  if(Serial.available > 0) {
    // If there is Serial date in the buffer
    byte recievedData = Serial.read();

    switch (recievedData):
    case START_MARKER:
      // Set begging buffer position
      break;
    case END_MARKER:
      // Set update frame flag
      break;
    default:
      // Add recieved data to buffer
      break;
  }
}

void updateFrame() {
  // Proccess buffer and update LEDS
}
