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

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
 #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

#include <PWMServo.h>
Servo myservo;
int pos = 0;


// Which pin on the Arduino is connected to the NeoPixels?

#define FACE_PIN   A1

// How many NeoPixels are attached to the Arduino?

#define FACE_COUNT 64


Adafruit_NeoPixel strip(FACE_COUNT, FACE_PIN, NEO_GRB + NEO_KHZ800);

#define DELAYVAL 200 // Time (in milliseconds) to pause between pixels


// Byte of array representing the address.
// This is the address where we will send the data.
// This should be same on the receiving side.
const byte address[6] = "01001";

// Motor controller pins
const int rightDirPin = 4;
const int rightPWMPin = 5;
const int leftDirPin = 7;
const int leftPWMPin = 6;





void setup() {

  // Motor controller pins
  pinMode(rightDirPin, OUTPUT);
  pinMode(leftDirPin, OUTPUT);


  myservo.attach(A2);

  Serial.begin(115200);

  // RF24 setup
  if (!radio.begin()) {
    Serial.println("radio  initialization failed");
    while (1)
      ;
  } else {
    Serial.println("radio successfully initialized");
  }
  radio.openReadingPipe(0, address);  // Destination address
  radio.setPALevel(RF24_PA_MIN);      // Min or max
  radio.startListening();             // sets  module as receiver

  #if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
#endif
  // END of Trinket-specific code.

//  pixels.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)
//  pixels.setBrightness(50);

  strip.begin();           // INITIALIZE NeoPixel strip object (REQUIRED)
  strip.show();            // Turn OFF all pixels ASAP
  strip.setBrightness(50); // Set BRIGHTNESS to about 1/5 (max = 255)

}
  

void loop() {
//  digitalWrite(2,HIGH);
//  digitalWrite(3,HIGH);
  
  uint8_t pipeNum;
  if (radio.available(&pipeNum))  //Looking for the data.
  {  
    int data;
    

    Serial.print("data available on pipe");
    Serial.println(pipeNum);

    radio.read(&data, sizeof(data));  //Reading the data
    Serial.print("data = ");
    Serial.println(data);
    

    switch (data) {
      case 0b00000100:
        Serial.println("turning right");
        strip.clear();
        strip.show();
        digitalWrite(rightDirPin, LOW);
        analogWrite(rightPWMPin, 255);
        break;
        
      case 0b00001000:
        Serial.println("forward");
        digitalWrite(rightDirPin, LOW);
        analogWrite(rightPWMPin, 255);
        digitalWrite(leftDirPin, HIGH);
        analogWrite(leftPWMPin, 50);
        strip.clear();
        strip.show();
        break;
        
      case 0b00010000:
        Serial.println("turning left");
        strip.clear();
        strip.show();
        digitalWrite(leftDirPin, HIGH);
        analogWrite(leftPWMPin, 50);
        break;
        
      case 0b00000010:
        Serial.println("backward");
        analogWrite(rightDirPin, 255);
        digitalWrite(rightPWMPin, LOW);
        analogWrite(leftDirPin, 50);
        digitalWrite(leftPWMPin, HIGH);
        strip.clear();
        strip.show();
        break;
        
      case 0b00001100:
      Serial.println("hello");
      
//      for(int i=0; i<FACE_COUNT; i++) {
//      strip.setPixelColor(i, strip.Color(0, 0, 255));
//      strip.show();
//      //delay(DELAYVAL); // Pause before next pass through loop
//    }

        strip.setPixelColor(19, 0, 0, 255);
        strip.setPixelColor(22, 0, 0, 255);
        strip.setPixelColor(26, 0, 0, 255);
        strip.setPixelColor(28, 0, 0, 255);
        strip.setPixelColor(29, 0, 0, 255);
        strip.setPixelColor(31, 0, 0, 255);
        strip.setPixelColor(35, 0, 0, 255);
        strip.setPixelColor(38, 0, 0, 255);
        strip.setPixelColor(43, 0, 0, 255);
        strip.setPixelColor(44, 0, 0, 255);
        strip.setPixelColor(45, 0, 0, 255);
        strip.setPixelColor(46, 0, 0, 255);

  for(pos = 0; pos < 180; pos += 1) { // goes from 0 degrees to 180 degrees, 1 degree steps
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
  for(pos = 180; pos>=1; pos-=1) {   // goes from 180 degrees to 0 degrees
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
    
      break;
      
      default:
        Serial.println("invalid code");
        stop();
        digitalWrite(rightDirPin, LOW);
        digitalWrite(rightPWMPin, LOW);
        break;
    }
  } else {
    //Serial.println("stop");
    stop();
    
  }
  delay(5);
}

void stop() {
  strip.clear();
  strip.show();
  digitalWrite(rightDirPin, LOW);
  analogWrite(rightPWMPin, 0);
  digitalWrite(leftDirPin, LOW);
  analogWrite(leftPWMPin, 0);
}
