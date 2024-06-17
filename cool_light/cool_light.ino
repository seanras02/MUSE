#include <Adafruit_NeoPixel.h>

#define trigPin 8
#define echoPin 9
#define LED_PIN 2      // Pin voor de WS2812B LED-strip
#define NUMPIXELS 200   // Aantal LEDs op je strip

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUMPIXELS, LED_PIN, NEO_GRB + NEO_KHZ800);

long duration;
int distance;
bool sensorActivated = false;  // Variabele om de sensoractivatie bij te houden

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  strip.begin();
  strip.show();  // Initialize all pixels to 'off'
  Serial.begin(9600);
}

void loop() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;

  Serial.print("Distance: ");
  Serial.println(distance);
   Serial.println(" cm");


  // Controleer of de sensor is geactiveerd (binnen 1 meter)
  if (distance < 100 && !sensorActivated) {
    sensorActivated = true;
    lightUpIndividually(2000);  // Licht elk LED afzonderlijk op gedurende 2 seconden
  } else if (distance >= 50) {
    sensorActivated = false;
  }
}

// Functie om elk LED afzonderlijk op te laten lichten
void lightUpIndividually(int duration) {
  for (int i = 0; i < 200; i++) {
    strip.setBrightness(30);
    strip.setPixelColor(i, strip.Color(255, 0, 0));  // Blauwe kleur, pas aan naar wens
    strip.show();
    delay(duration / strip.numPixels());


    strip.setPixelColor(i-50, strip.Color(0, 0, 0));  // Zet de LED weer uit
    strip.show();
  }

}