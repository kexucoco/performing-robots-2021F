/*
   Example using the nRF24L01 radio module to communicate 
   between two Arduinos,
   the transmitter is connected to some pushbuttons
   the receiver is connected to a motor driver
*/

// Pin usage
// nRF24L01 uses SPI which is fixed on pins 11, 12, and 13.
// It also requires two other signals
// (CE = Chip Enable, CSN = Chip Select Not)
// Which can be any pins:

const int CEPIN = 9;
const int CSNPIN = 10;

// In summary,
// nRF 24L01 pin    Arduino pin   name
//          1                     GND
//          2                     3.3V
//          3             9       CE
//          4             10      CSN  
//          5             13      SCLK
//          6             11      MOSI/COPI
//          7             12      MISO/CIPO   

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
RF24 radio(CEPIN, CSNPIN);  // CE, CSN

//set up the Neopixel

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
 #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

#define LED_PIN   A0
#define LED_COUNT 64

Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);



// Byte of array representing the address. 
// This is the address where we will send the data. 
// This should be same on the receiving side.
const byte address[6] = "00001";

// Motor controller pins
const int rightDirPin = 4;
const int rightPWMPin = 5;
const int leftDirPin = 7;
const int leftPWMPin = 6;


void setup() {

  // Motor controller pins
  pinMode(rightDirPin, OUTPUT);
  pinMode(leftDirPin, OUTPUT);

  Serial.begin(115200);

#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
clock_prescale_set(clock_div_1);
#endif

  strip.begin();           // INITIALIZE NeoPixel strip object (REQUIRED)
  strip.show();            // Turn OFF all pixels ASAP
  strip.setBrightness(50); // Set BRIGHTNESS to about 1/5 (max = 255)

  // RF24 setup
  bool retval = radio.begin();
  // Serial.println(retval);
  radio.openReadingPipe(0, address);  // Destination address 
  radio.setPALevel(RF24_PA_MIN);      // Min or max
  radio.startListening();             // sets  module as receiver

  
}

int lastButtonstate = LOW;
int motionState = LOW;
  
void loop() {

  int currentButtonstate = LOW;
  
  if (radio.available())  //Looking for the data.
  {
    int data;

    radio.read(&data, sizeof(data));  //Reading the data
    //Serial.println(data);

    switch (data) {
        break;
      case 0x01:
        Serial.println("button pressed");
        currentButtonstate = HIGH;
        break;
       case 0x02:
//        Serial.println("forward");
//        digitalWrite(rightDirPin, HIGH);
//        analogWrite(rightPWMPin, 0);
//        digitalWrite(leftDirPin, LOW);
//        analogWrite(leftPWMPin, 255);
        break;
      case 0x04:
//        Serial.println("turning left");
//         digitalWrite(rightDirPin, LOW);//
//        analogWrite(rightPWMPin, 200);//
//        digitalWrite(leftDirPin, HIGH);
//        analogWrite(leftPWMPin, 50);
          stop();
        break;
      default:
        Serial.println("invalid code");
//        stop();
//        digitalWrite(rightDirPin, LOW);
//        digitalWrite(rightPWMPin, LOW);
        break;
    }

    if ((lastButtonstate == LOW) && (currentButtonstate == HIGH)) { 
      motionState = 1-motionState;
      delay(10);
    }

    if (motionState == HIGH) {
     Serial.println("afraidmode");
     afraidmode();
    } else{
     Serial.println("calmmode");
     stop();
    }

    lastButtonstate = currentButtonstate;

    
  } else {
    Serial.println("stop");
    stop();

    //add code for quite mode
  }
  delay(5);
}


void colorWipe(uint32_t color, int wait) {
  for(int i=0; i<strip.numPixels(); i++) { // For each pixel in strip...
    strip.setPixelColor(i, color);         //  Set pixel's color (in RAM)
    strip.show();                          //  Update strip to match
    delay(wait);                           //  Pause for a moment
  }
  delay(2000);
}

void rainbow(int wait) {
  // Hue of first pixel runs ***1 complete loops through the color wheel.
  // Color wheel has a range of 65536 but it's OK if we roll over, so
  // just count from 0 to 5*65536. Adding 256 to firstPixelHue each time
  // means we'll make 5*65536/256 = 1280 passes through this outer loop:
  for(long firstPixelHue = 0; firstPixelHue < 1*65536; firstPixelHue += 256) {
    for(int i=0; i<strip.numPixels(); i++) { // For each pixel in strip...
      // Offset pixel hue by an amount to make one full revolution of the
      // color wheel (range of 65536) along the length of the strip
      // (strip.numPixels() steps):
      int pixelHue = firstPixelHue + (i * 65536L / strip.numPixels());
      // strip.ColorHSV() can take 1 or 3 arguments: a hue (0 to 65535) or
      // optionally add saturation and value (brightness) (each 0 to 255).
      // Here we're using just the single-argument hue variant. The result
      // is passed through strip.gamma32() to provide 'truer' colors
      // before assigning to each pixel:
      strip.setPixelColor(i, strip.gamma32(strip.ColorHSV(pixelHue)));
    }
    strip.show(); // Update strip with new contents
    delay(wait);  // Pause for a moment
  }
}

void afraidmode() {
  digitalWrite(rightDirPin, LOW);
  //digitalWrite(rightPWMPin, HIGH);
  analogWrite(rightPWMPin, 200);
  digitalWrite(leftDirPin, HIGH);
  //digitalWrite(leftPWMPin, LOW);
  analogWrite(leftPWMPin, 50);//

  //light transformation
  rainbow(3);
  colorWipe(strip.Color(255,   0,   0), 50); // Red
  
}

void stop() {

  digitalWrite(rightDirPin, LOW);
  analogWrite(rightPWMPin, 0);
  digitalWrite(leftDirPin, LOW);
  analogWrite(leftPWMPin, 0);
  colorWipe(strip.Color(  0,   0, 255), 50); // Blue
}
