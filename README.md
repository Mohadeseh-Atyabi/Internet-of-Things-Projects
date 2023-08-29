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

## Smart Parking
A commercial complex asked us to design a smart parking lot that would ease the work of parking attendants. The parking lot should include the following features:
- A light (LED) above each parking space should show the empty or full state of the parking space.
- The total number of empty capacities should be shown on the monitor (LCD).
- To enter the parking lot, each car first enters the ID and password in the keypad. If the information is confirmed and at least one parking space is empty, the parking door (servo motor) will open, and the appropriate message will be shown on the monitor. If the information is not confirmed or there is no parking space in the parking lot, the parking lot door will not open, and the appropriate message will be shown on the monitor.
- Each car also enters the information (ID and password) in the keypad when leaving. If the information is confirmed, the calculated payment amount is displayed on the monitor, and the parking lot door is opened.
- To calculate the parking fee, get the time each car was in the parking lot and display an amount on the LCD based on that.

For implementation, the following points should be considered:
- Consider the parking lot as one floor, each with three parking spaces.
- As an LCD, you can use LM041L to show the parking capacity information in the first line, the user's data during entry and exit, or the appropriate message in the last two lines.
- To detect the car in any clean place, use the PIR sensor and set its input (testPin) to 0 or 1.
- Assume that only a car may pass through a parking lot and does not intend to park. It is obvious that the parking light should only be turned on sometimes a car passes through the parking lot. We should be able to distinguish who just passed the parking lot and who wants to park there. According to the mentioned explanations, design this mechanism and solve the problem.
- The user must use the keypad to specify that he is entering or leaving the parking lot.
