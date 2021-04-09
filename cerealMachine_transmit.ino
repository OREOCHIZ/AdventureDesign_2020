//코드 안정화 삭제
// 초음파 센서 2개
// 서보모터랑 uart 통신까지
#include <LiquidCrystal_I2C.h>
#include <Wire.h>

LiquidCrystal_I2C lcd(0x3F, 16, 2);

int switch_ = 0; // while 문 탈출을 위한 변수
unsigned long previousMillis = 0; //delay를 쓰지 않으려는 발악
long interval = 5000; //delay를 쓰지 않으려는 발악

int IN1 = 3;
int IN2 = 4;
int ENA = 5;
int trig_1 = 7;
int echo_1 = 6;

int trig_2 = 9;
int echo_2 = 8;

int trig_3 = 10;
int echo_3 = 11;

int button_a = 12;
int button_b = 13;

int a_status = 0;
int b_status = 0;
int preva_status = 0;
int prevb_status = 0;

long distance_return(int trig, int echo);
void motor_go(int IN1, int IN2, int ENA);
void motor_go_slow(int IN1, int IN2, int ENA);
void motor_stop(int IN1, int IN2);
void sensor_Print(long distance);
void motor_too_slow(int IN1, int IN2, int ENA);

void setup() 
{

Serial.begin(9600);
pinMode(IN1, OUTPUT);
pinMode(IN2, OUTPUT);
pinMode(trig_1, OUTPUT);
pinMode(echo_1, INPUT);
pinMode(trig_2, OUTPUT);
pinMode(echo_2, INPUT);
pinMode(trig_3, OUTPUT);
pinMode(echo_3, INPUT);
pinMode(ENA, OUTPUT);

pinMode(button_a, INPUT);
pinMode(button_b, INPUT);

lcd.init();
lcd.backlight();
}

void loop() 
{
  while (switch_ == 0)
  {
  /* ♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥ 거리 받아오는 코드 ♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥*/
  long new_distance_1 = distance_return(trig_1, echo_1);
  long new_distance_2 = distance_return(trig_2, echo_2);
  long new_distance_3 = distance_return(trig_3, echo_3);

  /* ♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥ 거리 받아오는 코드 ♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥*/

  /* ♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥ if 문 1번 ♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥*/
  if (new_distance_1 < 50)
  {

    lcd.setCursor(0,0); 
    lcd.print("  a) Chocolate  ");     // 문구를 출력합니다.

    lcd.setCursor(0,1);
    lcd.print("    b) Berry    ");
    
    unsigned long currentMillis = millis(); 
    previousMillis = currentMillis;
    char num;
    a_status = digitalRead(12);
    b_status = digitalRead(13);
    
    
    
    while (currentMillis - previousMillis <= 10000)
    { 
      
      a_status = digitalRead(12);
      b_status = digitalRead(13);

      delay(300);
      motor_stop(IN1, IN2);
      
      if(a_status > preva_status)
      {
        lcd.clear();
        lcd.setCursor(0,0);           
        lcd.print("  Good Choice!  ");

        lcd.setCursor(0,1);         
        lcd.print("   Chocolate!   ");

        
        Serial.print("A");
        
      }

      else if(b_status > prevb_status)
      {
        lcd.clear();
        lcd.setCursor(0,0);          
        lcd.print("  Good Choice!  ");

        lcd.setCursor(0,1);       
        lcd.print("     Berry!     ");
        Serial.print("B");
        
      }
      
      currentMillis = millis(); 

      
    }
  
    if (currentMillis - previousMillis >= 10000)
    { 
      lcd.clear(); 
      motor_go(IN1, IN2, ENA);
      delay(2000);
      
    }
    
  }
/* ♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥ 두번째 if 문 ♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥*/


  else if (new_distance_2 < 50)
  {

    lcd.setCursor(0,0); 
    lcd.print("    Topping?    ");  

    lcd.setCursor(0,1);
    lcd.print("  a) YES b) NO  ");
    
    unsigned long currentMillis = millis(); 
    previousMillis = currentMillis;
    a_status = digitalRead(12);
    b_status = digitalRead(13);
    
    char num;

       
    while (currentMillis - previousMillis <= 10000)
    { 
      a_status = digitalRead(12);
      b_status = digitalRead(13);

      delay(300);
      motor_stop(IN1, IN2);

      
      if(a_status > preva_status)
      {
        lcd.clear();
        lcd.setCursor(0,0);         
        lcd.print("  Good Choice!  ");

        lcd.setCursor(0,1);         
        lcd.print("      YES!      ");
        Serial.print("a");
        
      }

      else if(b_status > prevb_status)
      {
        lcd.clear();
        lcd.setCursor(0,0);        
        lcd.print("  Good Choice!  ");

        lcd.setCursor(0,1);          
        lcd.print("       NO       ");
        Serial.print("b");
        
      }

    currentMillis = millis();
    
      
    }
  
    if (currentMillis - previousMillis >= 10000)
    { 
      lcd.clear();
      motor_go(IN1, IN2, ENA);
      delay(2000);
    }
    
  }

/* ♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥ 세번째 if 문 ♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥*/


  else if (new_distance_3 < 50)
  {

    lcd.setCursor(0,0); 
    lcd.print("  a) Cow Milk   ");     // 문구를 출력합니다.

    lcd.setCursor(0,1);
    lcd.print("  b) Soy Milk   ");
    
    unsigned long currentMillis = millis(); 
    previousMillis = currentMillis;
    
    char num;
    a_status = digitalRead(12);
    b_status = digitalRead(13);
    
    
    while (currentMillis - previousMillis <= 20000)
    { 

      a_status = digitalRead(12);
      b_status = digitalRead(13);

      delay(300);
      motor_stop(IN1, IN2);

      
      if(a_status > preva_status)
      {
        lcd.clear();
        lcd.setCursor(0,0);           // 1번째 줄 0번째 셀부터 입력하게 합니다.
        lcd.print("  Good Choice!  ");

        lcd.setCursor(0,1);           // 1번째 줄 0번째 셀부터 입력하게 합니다.
        lcd.print("    Cow Milk    ");
        Serial.print("c");
        
      }

      else if(b_status > prevb_status)
      {
        lcd.clear();
        lcd.setCursor(0,0);           // 1번째 줄 0번째 셀부터 입력하게 합니다.
        lcd.print("  Good Choice!  ");

        lcd.setCursor(0,1);           // 1번째 줄 0번째 셀부터 입력하게 합니다.
        lcd.print("    Soy Milk    ");
        Serial.print("d");
        
      }
      currentMillis = millis(); 
       

      
    }
  
    if (currentMillis - previousMillis >= 20000)
    { 
      lcd.clear();
      switch_ = 1;
      // previousMillis = 0;
      motor_go_slow(IN1, IN2, ENA);
      break;
    }
    
  }

 prevb_status = b_status;
 preva_status = a_status;
 motor_go(IN1, IN2, ENA);
 

 /* ♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥ while 문 끝났다 ♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥*/
}

}

/* ♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥사랑이 넘치는 함수 정의 파트♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥*/


long distance_return(int trig, int echo)
{
  long duration, distance;

  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);

  duration = pulseIn(echo, HIGH);

  distance = duration * 170 / 1000 ;


  return distance;
  
  
}

void sensor_Print(long distance)
{
  Serial.print("거리: ");
  Serial.print(distance);
  Serial.println("mm");
  delay(100);
}

void motor_go(int IN1, int IN2, int ENA)
{
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW); 
  analogWrite(ENA, 125); 
}

void motor_go_slow(int IN1, int IN2, int ENA)
{
    
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  for(int pwm =100; pwm>=1; pwm-=0.5)
  {
     analogWrite(ENA, pwm);
     delay(100);
  }

  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
}

void motor_stop(int IN1, int IN2)
{
  
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  
}
