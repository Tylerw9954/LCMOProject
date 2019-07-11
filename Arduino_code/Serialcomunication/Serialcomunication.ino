
// zoomkat 12-25-13 serial servo test
// type servo position 0 to 180 in serial monitor
// or for writeMicroseconds, use a value like 1500
// Send an a to attach servo or d to detach servo
// for IDE 1.0.5 and later
// Powering a servo from the arduino usually *DOES NOT WORK*.

#include <Servo.h> 
String readString; //String captured from serial port
Servo myservoB;  // create servo object to control a servo
Servo myservoT;  // create servo object to control a servo 
int topP; //value to write to servo
int botP; //value to write to servo
int n = 0;

void setup() {
  Serial.begin(9600);
  //myservoB.writeMicroseconds(1500); //set initial servo position if desired
  myservoB.attach(7, 500, 2500);  //the pin for the servo control, and range if desired
  myservoT.attach(9, 500, 2500);  //the pin for the servo control, and range if desired
  Serial.println("servo all-in-one test code 12-25-13"); // so I can keep track of what is loaded
  Serial.println();
}

void loop() {
  while (Serial.available()) {
    char c = Serial.read();  //gets one byte from serial buffer
    readString += c; //makes the string readString
    delay(2);  //slow looping to allow buffer to fill with next character
  }

  if (readString.length() >0) {
    Serial.println(readString);  //so you can see the captured string 

      // attach or detach servo if desired
    if (readString == "d") { 
      while (digitalRead(7)) {} //delay loop until pin 7 is low
      myservoB.detach(); //detach servo
      Serial.println("servo detached");
      goto bailout; //jump over writing to servo
    }
    if (readString == "a") {
      myservoB.attach(7); //reattach servo to pin 7
      Serial.println("servo attached");
      goto bailout;
    }    
    int first = readString.indexOf("=");
    int second = readString.indexOf(",");
    
String laserArg = readString.substring(0, first);
String botS = readString.substring(first+1, second);
String topS = readString.substring(second+1, readString.length());

Serial.println(laserArg); 
Serial.println(botS); 
Serial.println(topS); 

botP = botS.toInt();
topP = topS.toInt();


    n = 80;//readString.toInt();  //convert readString into a number

    // auto select appropriate value
    if(botP <= 200)
    {
      Serial.print("writing Bot Angle: ");
      Serial.println(botP);
      myservoB.write(botP);
    }

    if(topP <= 200)
    {
      Serial.print("writing Top Angle: ");
      Serial.println(topP);
      myservoB.write(topP);
    }
   

bailout: //reenter code loop
    Serial.print("Last servo command position Bot: ");    
    Serial.println(myservoB.read());
    Serial.print("Last servo command position Top: "); 
    Serial.println(myservoT.read());
    Serial.println();
    readString=""; //empty for next input
  }
}
