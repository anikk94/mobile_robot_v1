#include <SoftwareSerial.h>
SoftwareSerial espSerial(2, 3); //RX,TX
#define a 5
#define b 6
#define c 7
#define d 8
String response = "";
String userCommand = "";
char cResponse = '\0';
int response_count = 0;
void setup() {
  //======== serial port initializaition =========//
  Serial.begin(9600);
  espSerial.begin(9600);
  pinMode(a, OUTPUT);
  pinMode(b, OUTPUT);
  pinMode(c, OUTPUT);
  pinMode(d, OUTPUT);
  digitalWrite(a, HIGH);
  digitalWrite(b, HIGH);
  digitalWrite(c, HIGH);
  digitalWrite(d, HIGH);
  //=========== esp8266 device check =============//
  espSerial.println("AT");
  while (espSerial.available() <= 0) {
    ;
  }
  response = espSerial.readString();
  Serial.println(response);
  delay(5);
  espSerial.println("AT+CIPMUX=1");
  delay(1000);
  espSerial.println("AT+CIPSERVER=1,80");
  delay(1000);
  Serial.println("Startup Complete");
  //============== end of setup() ===============//

}


void loop() {
  if (Serial.available() > 0) { // if SerialMonitor cmd is available
    userCommand = Serial.readString();
    if (true) {
      espSerial.println(userCommand);
      Serial.println("\nuserCommand: " + userCommand);
    }
  }

  //  if (espSerial.available() > 0) {  // read esp8266 as string
  //    response = espSerial.readString();
  //    Serial.print(response);
  //  }

  if (espSerial.available() > 0) {
    cResponse = espSerial.read();
    if (cResponse != '\n') {
      response += cResponse;
    }
    else {
      Serial.println(response);
      // response_count = response.length();
      // Serial.println("  " + response_count);

      if (response == "w") {      // front
        digitalWrite(a, LOW);
        digitalWrite(b, HIGH);
        digitalWrite(c, HIGH);
        digitalWrite(d, LOW);
        delay(30);
      }
      else if (response == "a") { // left
        digitalWrite(a, LOW);
        digitalWrite(b, HIGH);
        digitalWrite(c, HIGH);
        digitalWrite(d, HIGH);
        delay(30);
      }
      else if (response == "s") { // back
        digitalWrite(a, HIGH);
        digitalWrite(b, LOW);
        digitalWrite(c, LOW);
        digitalWrite(d, HIGH);
        delay(30);
      }
      else if (response == "d") { // right
        digitalWrite(a, HIGH);
        digitalWrite(b, HIGH);
        digitalWrite(c, HIGH);
        digitalWrite(d, LOW);
        delay(30);
      }
      else {                      // stall
        digitalWrite(a, HIGH);
        digitalWrite(b, HIGH);
        digitalWrite(c, HIGH);
        digitalWrite(d, HIGH);
      }

      response = "";
    }
  }
  //  if (espSerial.available() > 0) {
  //    cResponse = espSerial.read();
  //    if (cResponse == '\n') {
  //      Serial.println(' ');
  //    }
  //    Serial.print(cResponse);
  //  }

}
