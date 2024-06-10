#include <Adafruit_NeoPixel.h>

const int LedPin = 2;           // Pin where LED strip is connected
const int AfstandTrig = 8;      // Ultrasonic sensor trigger pin
const int AfstandEcho = 9;      // Ultrasonic sensor echo pin
const int DISTANCE_THRESHOLD = 50; // Distance threshold to turn off the LED strip
const int NUM_LEDS = 30;        // Number of LEDs in your strip

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, LedPin, NEO_GRB + NEO_KHZ800);

void setup() {
  pinMode(AfstandTrig, OUTPUT);
  pinMode(AfstandEcho, INPUT);
  Serial.begin(115200);

  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
}

void loop() {
  // Send ultrasonic pulse
  digitalWrite(AfstandTrig, LOW);
  delayMicroseconds(2);
  digitalWrite(AfstandTrig, HIGH);
  delayMicroseconds(10);
  digitalWrite(AfstandTrig, LOW);

  // Measure the time it takes for the echo signal to return
  long duration = pulseIn(AfstandEcho, HIGH);
  int afstandWaarde = duration * 0.034 / 2;

  // Print the measured distance
  Serial.print("Afstand: ");
  Serial.print(afstandWaarde);
  Serial.println(" cm");

  // Check if the distance is less than the threshold
  if (afstandWaarde < DISTANCE_THRESHOLD) {
    // Turn on the LED strip
    for (int i = 0; i < NUM_LEDS; i++) {
      strip.setPixelColor(i, strip.Color(255, 255, 255)); // Set all LEDs to red
    }
    strip.show();
  } else {
    // Turn off the LED strip
    for (int i = 0; i < NUM_LEDS; i++) {
      strip.setPixelColor(i, strip.Color(0, 0, 0)); // Set all LEDs to off
    }
    strip.show();
  }

  delay(500); // Wait 1 second before checking again
}