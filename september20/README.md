## RobotSayHello Weekly Assignment

Video link for the project: https://youtu.be/XHk7ve81HAw

This is the final result:

![IMG_0545](https://user-images.githubusercontent.com/57734650/133886321-ceae1f76-c3b9-4df8-82de-afcb175d044b.jpg)

**My definition of the word "robot":**

A robot is a physical machine built on computer algorithms. It should have **interaction** with the outside world and convey message/feedback autonomously according to its built-in functions. It might be humanroid, while it is not necessary.

**Building Process:**

I come up with the idea to make the robot stand with two wheels. So I used the hot glue gun to stick two DC motor onto the cardboard. The arrangement of battery, arduino and H-bridge was a little bit annoying, as I had been away from physical production for a while. I used tape to stick those parts onto the cardboard to avoid damaging them. I arranged the H-bridge onto the back side so that it was near the DC motors. Then I tested the original version, wrote codes for it to go straight and controlled its speed. It was disappointed that I had to link the USB cable like a tail to it as I failed to find another suitable power. The result was ideal so I decided to add a servo motor to help it convey some messages. I designed a pillar to hold the servo motor and sticked a cardboard onto it saying hello! According to my design of story, I coded the robot to turn around first and say hello by rotating the servo motor. I adjusted the differences of the speed of two wheels so that they can trun around smoothly. Then that is it, the robot say hello! (The code is in the same folder named  "HW2.ino")

Here are some production images:

Original version with two wheels:

![IMG_0540](https://user-images.githubusercontent.com/57734650/133886308-31c2dc40-7d04-4b2e-80f6-1e1cef876858.jpg)
![IMG_0541](https://user-images.githubusercontent.com/57734650/133886311-9e141a25-711b-457f-9ccf-4b209360c998.jpg)

The pillar for the servo motor:

![IMG_0542](https://user-images.githubusercontent.com/57734650/133886315-6c7052db-aa25-4eee-9b6b-8b9565d9ae42.jpg)

The cardboard saying hello in English and Chinese:

![IMG_0543](https://user-images.githubusercontent.com/57734650/133886318-c608777c-0eae-4572-979d-dc9b3d18e2dc.jpg)

The servo motor:

![IMG_0544](https://user-images.githubusercontent.com/57734650/133886320-7ce57301-4e88-4642-be6d-af5ac2acd345.jpg)


**Describe the story and how the movement sequence tells it:**

I am initially inspired by the Space class I take this semester. On that course we learned the history of space exploration, including the Apollo Lunar Roving Vehicle and the Kepler detector. They all take the responsibility of explore the depth of universe and convey human message to the space, which is aligned with my definition of robot with interaction and communication. So the basic story for this robot is it was firstly located on a infamiliar place, it wanted to look around to find anything alive and similar to itself. It was confused at first so it turn around without purpose (a full circular move), then it found something and moved there to say hello (rotating the message board) and continue its task…

**Describe any difficulties you had and how you overcame them or worked around them:**

I think the physical production and lack of portable power unit are two main difficulities I met. It was hard for me to stick the motors onto the cardboard as the hot glue did not seem to be very strong, so I tried several times to remove and stick again and again. I also tried a set of combinations to make the robot stand with balance, which is why I put the heavier baterry on the side. I also arranged the arduino on the side to make it easier to connect the cables and jumper wires. Lack of portable power unit make me yield to use the USB cable which sometimes looks like I am walking my robot dog. I also failed to add some switches so for now it will perform whenever the power is on. Hopefully I can improve this part with next week's state machine class?

**Describe anything interesting you learned or discovered:**

After a short discussion with Zhiyang, we agree that changing the message to "Hello World" which will be more robotic. It sounds quite interesting for me since it refreshes my memory when I first entered the coding world :) But I preserved the original version of message as I loved the chinese characters on it. Another interesting part is the time consumed. Even such a weekly assignment spent my quite a while to brainstorm and produce. Hard to imagine more fancy projects, but it is a lot of fun!

