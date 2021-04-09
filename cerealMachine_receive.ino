//받아오는 부분
#include <Servo.h>
Servo servo;
Servo servo2;

int IN1 = 3;
int IN2 = 4;

int IN3 = 5;
int IN4 = 6;


void setup() {
  Serial.begin(9600);
  servo.attach(13);
  servo2.attach(12);

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  
}

void loop() {
  if(Serial.available())
  {

  char Data = (char)Serial.read();

  if(Data == 'A')
  {
  
    servo.write(180);
    delay(1000);
    
  }
  else if (Data == 'B')
  {
    
    servo.write(0);
    delay(1000);
  }

  else if (Data == 'a')
  {
    servo2.write(180);
    delay(1000);
  }

  else if (Data == 'b')
  {
    servo2.write(90);
    
  }

else if (Data == 'c')
  {
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);

    delay(5000);
    
  }

  else if (Data == 'd')
  {
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);

    delay(5000);
    
  }

  servo.write(90);
  servo2.write(90);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  
}

}
