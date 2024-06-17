#include <Adafruit_NeoPixel.h>

#define trigPin 8
#define echoPin 9
#define LED_PIN 2      // Pin voor de WS2812B LED-strip
#define NUMPIXELS 201   // Aantal LEDs op je strip

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUMPIXELS, LED_PIN, NEO_GRB + NEO_KHZ800);

long duration;
int distance;
bool sensorActivated = false;  // Variabele om de sensoractivatie bij te houden
bool isLEDOn = false;

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
    if (!isLEDOn){
      coolEffect(255, 0, 0, 5);
      isLEDOn = true;
    }else{
      turnOffAllLEDs();
      isLEDOn = false;
    }
  } else if (distance >= 100) {
    sensorActivated = false;
  }
}

void coolEffect(uint8_t r, uint8_t g, uint8_t b, uint8_t wait) {
  for (int i = 0; i < strip.numPixels(); i++){
    strip.setPixelColor(i, strip.Color(r, g, b));
    strip.show();
    delay(wait);
    strip.setPixelColor(i, strip.Color(0,0,0));
  }
  for (int i = strip.numPixels() - 1; i >= 0; i--){
    strip.setPixelColor(i, strip.Color(r, g, b));
    strip.show();
    delay(wait);
  }
}

// alle leds uit
void turnOffAllLEDs(){
  for (int i = 0; i < strip.numPixels(); i++){
    strip.setPixelColor(i, strip.Color(0, 0, 0));
  }
  strip.show();
}