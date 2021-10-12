
## Midterm Project -- Emergency Intelligencer

My robot will be a rotating machine with a shiny alien head which will shake and rotate to convey the emergency status. 

![IMG_1207](https://user-images.githubusercontent.com/57734650/136968512-07c8466d-4a31-4b6f-8c3b-023a94b9b2e1.jpg)

Here is the link for the demo: https://youtu.be/NN6xslbjXJY

The illustration prototype is visualized here:

![IMG_84C0F486D3CD-1](https://user-images.githubusercontent.com/57734650/135748669-0e93812f-db32-41aa-89ca-a0172e389d6f.jpeg)

**Actuators needed:** 2 DC motors, NeoPixel matrix.

**Building parts (ideal):** It will have a circular body built with cardboard, arduino uno, batteries and H-bridge. Two DC motors will be sticked onto it and linked with two wheels. Another wheel will also be attached but without motor to make things easier. For the head part, I will make four springs to hold the NeoPixel so that it will shake with movement. Hope those solid wires will help me make the springs. On the Neopixel board, I intend to make a dome-like cover to serve as the cute head of the robot, and light should be transfer through the material.

**How it will be expressive:** The emotion will be demonstrated through the rotation and light change. For instance, when the robot is calm, it will stand still and with its blue head shining. Then the emergency happens. Its head will blink with rainbow color to show the emergency status. Then it will rotate quickly and its head will turn red with the movement. More advancedly with the romote control, I can use the botton to trigger the emergency status with rotation. Maybe I can add a sound part to build the senario.

**Current Progress and What Left:**


**Construction Part:**

1. Use solid wires to make springs. Connect it to the NeoPixel.
![IMG_1156](https://user-images.githubusercontent.com/57734650/135758505-7823ddfe-a9eb-4c61-9905-d406d0270dcf.jpg)
![IMG_1157](https://user-images.githubusercontent.com/57734650/135758510-54d29db9-6d2c-45f2-bb0d-625660de677c.jpg)
![ezgif com-video-to-gif-2](https://user-images.githubusercontent.com/57734650/135758515-fbb59c4e-0073-4ec1-96bb-2c11ca40d64a.gif)

2. Use hot glue gun to stick the motors to the board. Make a flexible wheel which took a long time. I use the coffee stirrers to link the wire and use tapes to make the pipeline. **Problems: Hard to arrange things, a breadboard is used as the GND on the arduino board is not enough. (Maybe can solder them to make it take less space) Batteries are heavy and it make the board fold. (Add solid sticks on the back and cut the angle of cardboard.)**
![IMG_1158](https://user-images.githubusercontent.com/57734650/135758820-32fa8eab-512c-4c72-a57e-801649b80763.jpg)
![IMG_1161](https://user-images.githubusercontent.com/57734650/135758813-55c21700-c2be-4225-bdbe-b4a92b2b2cea.jpg)

3. Add the Neopixel board to the main machine via several pillars made from toilet paper tube. **(Head cover missed, still finding appropriate material)**



![IMG_1159](https://user-images.githubusercontent.com/57734650/135758955-0f1abbb2-0bc9-449e-85cc-bd5127bd1eee.jpg)

4. Built radio remote control. Current progress is click the button, the robot starts to rotate. **(Neopixel Sequence Missing. Will made that later. More coding later.)**



![IMG_1163](https://user-images.githubusercontent.com/57734650/135759231-f58995cd-c459-4f3f-a844-a01790c25ace.jpg)
![ezgif com-video-to-gif-3](https://user-images.githubusercontent.com/57734650/135759112-7fe7fca0-d65d-4f2c-b29a-381e85aa7b9f.gif)

5. Rearrange differnet parts of the robot and fix them on the main body, making it more easier to work with the wires.

![IMG_1180](https://user-images.githubusercontent.com/57734650/136068127-8245e128-4a49-4ab1-a7f0-1a0b7761a06d.jpg)

Less messy now!

![ezgif com-video-to-gif](https://user-images.githubusercontent.com/57734650/136068471-b85abe77-8a08-43cd-a20a-7586c5c65889.gif)

6. Resolder the wires for Neopixel as the original one is too short, test the Neopixel, build the curcuit. **(Learning the Neopixel coding...)**

7. Made the shaking head using plastic bag and connect it to the neopixel board. I love the cross stick design which made the head stand!


![IMG_1204](https://user-images.githubusercontent.com/57734650/136654153-7f189b68-ca8e-452d-94bd-b5d060937ba6.jpg)
![IMG_1205](https://user-images.githubusercontent.com/57734650/136654155-c62f3d0c-4561-4f0d-99f5-6f669238080b.jpg)


8. Add two eyes made of paper and solid string springs. This is what the robot looks like now:

![IMG_1206](https://user-images.githubusercontent.com/57734650/136654229-78a51b6c-9ee3-4be5-aab9-bf228d6ae2a0.jpg)


**Coding Part:**

1. Referring to the class example, I made the radio connection between the button and robot. Robot rotation is easier to make while the difficulty is arrange all the electronics onto the robot and make it rotate stably. One main problem I met with the coding part is the application of state machine:

```

int lastButtonstate = LOW;
int motionState = LOW;
  
void loop() {

  int currentButtonstate = LOW;
  
  if (radio.available())  //Looking for the data.
  {
    int data;

    radio.read(&data, sizeof(data));  //Reading the data

    switch (data) {
        break;
      case 0x01:
        Serial.println("button pressed");
        currentButtonstate = HIGH;
        break;
      case 0x02:
        break;
      case 0x04:
          stop();
        break;
      default:
        Serial.println("invalid code");
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
   
```

I think the code itself works fine. But the problems lies on the fact that the transmitter will send a sequence of 1 to the receiver and then the motionState will not be stable as the received signal contains several pairs of start and stop signal. For the demo video, when I press the start button, it starts to rotate but theoretically it should continue to rotate until I press the button again. But the fact is that it sends several 1 signal and the robot will stop automatically. I think the robot in the demo is expressive and conveys the emergency status. But I hope I can figure out this state machine problem next class.

Current Progress: link for the demo: https://youtu.be/rxnX0yNpkiw

===> Problem solved: The automatic stop resulted from the existence of stop() when the radio is unavailable. Also, I finally figured out I forgot to update the lastButtonstate when the radio is unavailabe. So the mistake is when the button is first pressed, the last button state will always be high as long as the radio is unavailable. I remove the stop() function and update the last button state to be LOW when the radio is unavailable. To initiate the robot, I add the stop() in the setup.

2. I adjust the colorswipe function and rainbow function built for Neopixel to help the robot show different expressions.

3. To make the robot more expressive, I add the breathing effect for it, make the head have gradual light luminosity change which looks like it is alive. The rainbow function is removed from the main motion functions and only exists in the transformation stage to show the robot is changing status.

  I set different brightness for the Neopixel to do the breathing effect:
  
  ```
  for (int i=50; i>0; i--) { strip.setBrightness(i); strip.show(); delay(10); }
  delay(1000);
  for (int k=1; k<50; k++) { strip.setBrightness(k); strip.show(); delay(10); }
  ```
  
**Further Improvement:**

1. I took a while to make those springs and hope to see a shaking head when the robot rotates. However, the wires under the neopixel and the unstable plastic head makes the shaking not so obvious. Hope I can find more suitable material to trigger such effect next time.

2. I think sound will help the robot to be much more expressive. I did not use buzzer for the time limit this time. Alternatively, I add sound via video editing. Hope next time I can use the buzzer to make live show!


