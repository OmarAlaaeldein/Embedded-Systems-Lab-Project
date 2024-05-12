#include <LiquidCrystal.h> //Load Liquid Crystal Library
LiquidCrystal LCD = LiquidCrystal(12, 11, 2, 3, 4, 5);  //Create Liquid Crystal Object called LCD
#
#define trigPin 6 //Sensor Echo pin connected to Arduino pin 6
#define echoPin 7 //Sensor Trip pin connected to Arduino pin 7
#define ledpinred 8
#define ledpinyellow 9
#define ledpingreen 10

  
  
void delayms(int n){
 for (int i=0;i<n;i++){
 TCNT0=0;
 OCR0A=250;
 TCCR0A=2; // CTC mode 
 TCCR0B=3; // timer is on , and prescaler
 while((TIFR0 &2)==0);
 TIFR0=2; // clears TOV0
 
 }
 TCCR0A=0;
 TCCR0B=0;
}
void setup() 
{  
  DDRD|=0b01000000;
  //pinMode(trigPin, OUTPUT);
  //pinMode(echoPin, INPUT);
  //pinMode(ledpinred, OUTPUT);
  //pinMode(ledpingreen, OUTPUT);
  //pinMode(ledpinyellow, OUTPUT);
  DDRB|=0b00000111;
  LCD.begin(16,2); //Tell Arduino to start your 16 column 2 row LCD
  LCD.setCursor(0,0);  //Set LCD cursor to upper left corner, column 0, row 0
  LCD.print("Target Distance:");  //Print Message on First Row
  delayms(250);
}

void loop() {
  
  long duration, distance;
  int sensorValue = analogRead(A0); 
  int range = map(sensorValue, 0, 1023, 1, 6); // 5 modes
  PORTD&=0b10111111;
  PORTD|=0b01000000;
  //digitalWrite(trigPin, LOW);
  //digitalWrite(trigPin, HIGH);
  delayMicroseconds(10); // 10us ttl
  PORTD&=0b10111111;
  //digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration/2) / 29.1;
  LCD.print("Distance: ");
  if (distance<=20*range){
    PORTB=0b00000001;
    //digitalWrite(ledpinred, HIGH);
    delayms(250);
    //digitalWrite(ledpinred,LOW);
    PORTB=0b00000000;
  }
  else if((distance<=50*range)&&(distance>=20*range)){
    PORTB=0b00000010;
    //digitalWrite(ledpinyellow, HIGH);
    delayms(250);
    //digitalWrite(ledpinyellow,LOW);
    PORTB=0b00000000;
    }
  else{
    PORTB=0b00000100;
    //digitalWrite(ledpingreen, HIGH);
    delayms(250);
    //digitalWrite(ledpingreen,LOW);
    PORTB=0b00000000;
  } 
  LCD.setCursor(0,1);  //Set cursor to first column of second row
  delayms(500);
  LCD.setCursor(0,1);   //Set Cursor again to first column of second row
  LCD.print(distance); //Print measured distance
  LCD.print(" cm");
  delayms(500); //pause to let things settle
  LCD.clear();
}
