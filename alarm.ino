/*
  Alarm

*/

int led = 5;           // the PWM pin the LED is attached to
int motor =4;

int brightness = 0;    // how bright the LED is
int fadeAmount = 0;    // how many points to fade the LED by
int dir = -1;

char com;
int param;
String buf;

// the setup routine runs once when you press reset:
void setup() {
  // declare pin 9 to be an output:
  pinMode(led, OUTPUT);
  pinMode(motor, OUTPUT);
  Serial.begin(9600);
}

// the loop routine runs over and over again forever:
void loop() {
  if (Serial.available()) {
    buf = Serial.readString();// read the incoming data as string
    com = buf.charAt(0);
    param = buf.substring(1).toInt();

    switch (com) {
      case 'L':
        fadeAmount = constrain(param,0,30);
        Serial.println("Ok");  
        break;
      case 'M':
        if (param == 1)
          digitalWrite(motor,HIGH);
        else
          digitalWrite(motor,LOW);
        Serial.println("Ok");  
        break;
      case 'A':  
        if (param == 1){
          digitalWrite(motor,HIGH);
          fadeAmount = -1;          
        } else {
          digitalWrite(motor,LOW);
          fadeAmount = 0;
        }
        Serial.println("Ok");       
        break;
      default:
        Serial.println("Error");       
        break;
    }
  }

  if (fadeAmount > 0){
    // change the brightness for next time through the loop:
    brightness = constrain(brightness + fadeAmount * dir,0,255);
 
    // reverse the direction of the fading at the ends of the fade:
    if (brightness == 255 || brightness == 0 ) dir = - dir;
  
    // wait for 30 milliseconds to see the dimming effect
    analogWrite(led, brightness);
    delay(30);
  } else if(fadeAmount == 0) {
    analogWrite(led, 0);    
  } else {
    analogWrite(led, 255);    
  }

}
