# robot-arm-serial-controller
Robot arm controller for LeArm robot arm using serial in qt

## Guide for using the controller

### arduino_pc_serial_test: Check the serial communication between Arduino board and Windows PC

0. Download this repo, goto the `robot-arm-serial-controller/executable/arduino_pc_serial_test/`
1. Connect Arduino Uno with PC using USB cable.
2. Copy and download the arduino code to the board. (arduino/adapter.ino)
3. Start `robot_arm_serial_controller.exe` under `/pc` and start the test.
    - click "show ports"
    - click the port from the list and then click "select"
    - slide the slider to any position.
    
    the Arduino Uno build-in LED will toggle (slider value / 100) times, just try different values and check the toggle time.
    for example, slider value 1234, toggle 12 times, 580 -> 5 times.


### robot_arm_controller: the full controller program.

1. goto `robot-arm-serial-controller/arduino/adapter/` and copy the entire adapter folder and open it in Arduino IDE, then download the code to the board.
2. wire the Arduino Uno & robot arm mainboard:

   mainboard --------- Arduino
   
   5V <----------------> 5V
   
   RX <----------------> 11
   
   TX <----------------> 10
   
   GND <-------------> GND
   
3. power on the robot arm and turn on the switch, then connect Arduino Uno to PC with USB cable.
4. start the `robot_arm_serial_controller.exe` in `robot-arm-serial-controller/executable/robot_arm_controller/`
5. start playing:
    - select the port same as above.
    - click reset button to make robot arm move to default middle position.
    - play with the sliders, the motors should be controlled as expected.

## If anything looks unnormal, just shutdown the arobot arm.
