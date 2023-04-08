int LED1 = 2;
int LED2 = 11;
int LED3 = 10;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(Serial.available()) {
    String command = Serial.readStringUntil('\n');
    if (command == "ON") {
      digitalWrite(LED1, HIGH);
      digitalWrite(LED2, HIGH);
      digitalWrite(LED3, HIGH);

      Serial.println("Turn LED ON");
    } else if (command == "OFF") {
      digitalWrite(LED1, LOW);
      digitalWrite(LED2, LOW);
      digitalWrite(LED3, LOW);
      Serial.println("Turn OFF LED");

    } else if (command == "LED1") {
      digitalWrite(LED1, HIGH);
      digitalWrite(LED2, LOW);
      digitalWrite(LED3, LOW);
      Serial.println("Turn ON LED1");

    } else if (command == "LED2") {
      digitalWrite(LED2, HIGH);
      digitalWrite(LED1, LOW);
      digitalWrite(LED3, LOW);

      Serial.println("Turn ON LED2");
    } else if (command == "LED3") {
      digitalWrite(LED3, HIGH);
      digitalWrite(LED1, LOW);
      digitalWrite(LED2, LOW);

      Serial.println("Turn ON LED3");
    }
  }
}
