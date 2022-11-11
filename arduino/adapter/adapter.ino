//String data = "6,1234,1500";

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
}

void toggleLED(int c) {
  for (int i = 0; i < c; i++){
    digitalWrite(LED_BUILTIN, HIGH);
    delay(500);
    digitalWrite(LED_BUILTIN, LOW);
    delay(500);
  }
 
}

void loop() {
  // put your main code here, to run repeatedly:
  String data = Serial.readString();
  if (data.length() != 0) {
    digitalWrite(LED_BUILTIN, HIGH);
  }
  /*
  int x1 = data.indexOf(",");
  int x2 = data.indexOf(",", x1+1);
  int motor = data.substring(0, x1).toInt();
  int angel = data.substring(x1+1, x2).toInt();
  int time = data.substring(x2+1).toInt();
  if (motor == 6 && time == 1500){
    toggleLED(10);
  }
  else {
    toggleLED(2);
  }
  Serial.flush();
  */
}

