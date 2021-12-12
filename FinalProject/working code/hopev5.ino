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
//#include <Servo.h>
PWMServo myservo;
int pos = 0;


// Which pin on the Arduino is connected to the NeoPixels?

#define FACE_PIN   A1

// How many NeoPixels are attached to the Arduino?

#define FACE_COUNT 75


Adafruit_NeoPixel strip(FACE_COUNT, FACE_PIN, NEO_GRB + NEO_KHZ800);

//#define DELAYVAL 200 // Time (in milliseconds) to pause between pixels


// Byte of array representing the address.
// This is the address where we will send the data.
// This should be same on the receiving side.
const byte address[6] = "00009";

// Motor controller pins
const int rightDirPin = 4;
const int rightPWMPin = 5;
const int leftDirPin = 7;
const int leftPWMPin = 6;

int buttons;
int potentiometer;


void setup() {

  // Motor controller pins
  pinMode(rightDirPin, OUTPUT);
  pinMode(rightPWMPin, OUTPUT);
  pinMode(leftPWMPin, OUTPUT);
  pinMode(leftDirPin, OUTPUT);


  myservo.attach(3);

  Serial.begin(115200);

  //Neopixel setup
  #if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
  #endif
  strip.begin();           // INITIALIZE NeoPixel strip object (REQUIRED)
  strip.show();            // Turn OFF all pixels ASAP
  strip.setBrightness(50); // Set BRIGHTNESS to about 1/5 (max = 255)

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

}
  

void loop() {
  
  uint8_t pipeNum;
  if (radio.available(&pipeNum))  //Looking for the data.
  {  
    int data[2];   

//    Serial.print("data available on pipe");
//    Serial.println(pipeNum);
    radio.read(&data, sizeof(data));  //Reading the data
//    Serial.print("data = ");
//    Serial.println(data);
    buttons = data[0];
    potentiometer = data[1];
    
    myservo.write(potentiometer);

    switch (buttons) {
      case 0b00000100:
        Serial.println("turning right");
        calm();
        digitalWrite(rightDirPin, LOW);
        analogWrite(rightPWMPin, 255);
        break;
        
      case 0b00001000:
        Serial.println("forward");
        digitalWrite(rightDirPin, LOW);
        analogWrite(rightPWMPin, 255);
        digitalWrite(leftDirPin, HIGH);
        analogWrite(leftPWMPin, 50);
        calm();
        break;
        
      case 0b00010000:
        Serial.println("turning left");
        calm();
        digitalWrite(leftDirPin, HIGH);
        analogWrite(leftPWMPin, 50);
        break;
        
      case 0b00000010:
        Serial.println("backward");
        analogWrite(rightDirPin, 255);
        digitalWrite(rightPWMPin, LOW);
        analogWrite(leftDirPin, 50);
        digitalWrite(leftPWMPin, HIGH);
        calm();
        break;
        
      case 0b00001100:
      Serial.println("hello");
      angry(); 
      break;
      
      default:
        Serial.println("invalid code");
        calm();
        stop();
//        digitalWrite(rightDirPin, LOW);
//        digitalWrite(rightPWMPin, LOW);
        break;
    }
  } else {
    //Serial.println("stop");
    calm();   
    stop();
    
  }
  delay(5);
}

void stop() {
  digitalWrite(rightDirPin, LOW);
  analogWrite(rightPWMPin, 0);
  digitalWrite(leftDirPin, LOW);
  analogWrite(leftPWMPin, 0);
}

void calm(){
  strip.setPixelColor(16, 0, 0, 255);
  strip.setPixelColor(17, 0, 0, 255);
  strip.setPixelColor(18, 0, 0, 255);
  strip.setPixelColor(21, 0, 0, 255);
  strip.setPixelColor(22, 0, 0, 255);
  strip.setPixelColor(23, 0, 0, 255);
  strip.setPixelColor(24, 0, 0, 255);
  strip.setPixelColor(26, 0, 0, 255);
  strip.setPixelColor(27, 0, 0, 255);
  strip.setPixelColor(28, 0, 0, 255);
  strip.setPixelColor(29, 0, 0, 255);
  strip.setPixelColor(31, 0, 0, 255);
  strip.setPixelColor(32, 0, 0, 255);
  strip.setPixelColor(33, 0, 0, 255);
  strip.setPixelColor(34, 0, 0, 255);
  strip.setPixelColor(37, 0, 0, 255);
  strip.setPixelColor(38, 0, 0, 255);
  strip.setPixelColor(39, 0, 0, 255);  
  strip.setPixelColor(50, 0, 0, 255);
  strip.setPixelColor(51, 0, 0, 255);
  strip.setPixelColor(52, 0, 0, 255);
  strip.setPixelColor(53, 0, 0, 255);
  strip.setPixelColor(70, 0, 0, 255);
  strip.setPixelColor(71, 0, 0, 255);
  strip.show();  
  
  }

void angry(){
  strip.setPixelColor(16, 255, 0, 255);
  strip.setPixelColor(17, 255, 0, 255);
  strip.setPixelColor(18, 255, 0, 255);
  strip.setPixelColor(21, 255, 0, 255);
  strip.setPixelColor(22, 255, 0, 255);
  strip.setPixelColor(23, 255, 0, 255);
  strip.setPixelColor(24, 255, 0, 255);
  strip.setPixelColor(26, 255, 0, 255);
  strip.setPixelColor(27, 255, 0, 255);
  strip.setPixelColor(28, 255, 0, 255);
  strip.setPixelColor(29, 255, 0, 255);
  strip.setPixelColor(31, 255, 0, 255);
  strip.setPixelColor(32, 255, 0, 255);
  strip.setPixelColor(33, 255, 0, 255);
  strip.setPixelColor(34, 255, 0, 255);
  strip.setPixelColor(37, 255, 0, 255);
  strip.setPixelColor(38, 255, 0, 255);
  strip.setPixelColor(39, 255, 0, 255);
  strip.setPixelColor(50, 255, 0, 255);
  strip.setPixelColor(51, 255, 0, 255);
  strip.setPixelColor(52, 255, 0, 255);
  strip.setPixelColor(53, 255, 0, 255);
  strip.setPixelColor(68, 255, 0, 255);
  strip.setPixelColor(69, 255, 0, 255);
  strip.show(); 

  delay(300);
  
  }


 
