#include "LobotServoController.h"

#define rxPin 10  // connect to tx pin on robot arm
#define txPin 11  // connect to rx pin on robot arm

SoftwareSerial mySerial(rxPin, txPin);
LobotServoController myse(mySerial);

void setup() {
  // put your setup code here, to run once:
  mySerial.begin(9600);
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
}

void toggleLED(int c) {
  for (int i = 0; i < c; i++){
    digitalWrite(LED_BUILTIN, HIGH);
    delay(200);
    digitalWrite(LED_BUILTIN, LOW);
    delay(200);
  }
}

// in arduino, int and long are all int32_t, so int to uint: -2147483648
uint8_t int_to_uint8(int num) {
  return (uint8_t)(num - -2147483648);
}

uint16_t int_to_uint16(int num) {
  return (uint16_t)(num - -2147483648);
}
void sendCmd(int motor, int angle, int time) {
  myse.moveServo(int_to_uint8(motor), int_to_uint16(angle), int_to_uint16(time));
  Serial.println(int_to_uint8(motor));
  Serial.println(int_to_uint16(angle));
  Serial.println(int_to_uint16(time));
}

void parse_and_send_cmd(String &data) {
  int x1 = data.indexOf(",");
  int x2 = data.indexOf(",", x1+1);
  int motor = data.substring(0, x1).toInt();
  int angle = data.substring(x1+1, x2).toInt();
  int time = data.substring(x2+1).toInt();
  sendCmd(motor, angle, time);
}

void loop() {
  // put your main code here, to run repeatedly:
  String data = Serial.readStringUntil('\n');
  if (data.length() == 0) {
    return;
  }
  parse_and_send_cmd(data);
}

