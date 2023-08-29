# Internet-of-Things-Projects

## Button
Make a replacement for a push switch to turn the LED on and off using an LDR. Note that the key must save its previous state. For example, if you put your hand in front of the LDR once and remove it, the LED will turn on and stay on, and when you place your hand near the LDR again, the LED will turn off. (To simulate in Proteus, change the LDR resistance manually.)

## Smart Umbrella
Consider we are supposed to make smart umbrellas for the restaurant tables. When at least one of the following situations occurs, this umbrella opens:  
- The rain is detected by the water sensor.
- Solar radiation is recognized by the LDR resistor.

The umbrella should be closed if none of the aforementioned circumstances apply. The servo motor rotates completely to perform the opening and closing.

## Pet Food Tank
In this question, we are going to make a food tank for pets. This system includes a servo motor, buzzer, light (LED), and load cell sensor. This system should feed the pet every three hours. Every three hours, it measures the weight of the container inside the tank with the Load Cell sensor. If the food is inside the container, the lid of the tank is opened by the servo motor, and the green light turns on. Then, after five minutes, the door is closed, and the light turns off. Now, if the amount of food in the container is small or there is no food in it, the tank door will not open, the buzzer will sound, and the red light will be on until the food container inside the tank is full.
