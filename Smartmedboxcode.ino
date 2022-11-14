#include <RTClib.h>
#include <Wire.h>
#include<EEPROM.h>
#include <LiquidCrystal.h>

LiquidCrystal lcd(9, 8, 7, 6, 5, 4); 
RTC_DS3231 rtc;
int temp,inc,hours1,minut,add=11;
int next=10;    
int INC=11;
int butt=12;
int set_mad=0;
int led1 = 3;
int led2 = 2;
int led3 = A3;

#define buzzer 13

int HOUR,MINUT,SECOND;

void setup()
{
 Serial.begin(9600);
 Wire.begin();
 lcd.begin(16,2);
 pinMode(INC, INPUT);
 pinMode(next, INPUT);
 pinMode(set_mad, INPUT);
 pinMode(led1,INPUT);
 pinMode(led2,INPUT);
 pinMode(led3,INPUT);
 pinMode(buzzer, OUTPUT);

   lcd.setCursor(0,0);
   lcd.print("SMART ");
   lcd.setCursor(0,1);
   lcd.print("  MEDICINE BOX  ");
    delay(2000);
     lcd.clear();
    lcd.setCursor(0,0);
   lcd.print(" TEAM HYDRA ");
   lcd.setCursor(0,1);
   lcd.print("    GVP ");
   delay(2000);
  if (! rtc.begin())
  {
    while (1);
  }

  if (rtc.lostPower())
  {
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }
}

void loop()
{
   int temp=0,val=1,temp4;
   DateTime now = rtc.now();
   if(digitalRead(butt)==0) //set medicine time 
     {
      lcd.setCursor(0,0);
   lcd.print("  Set Medicine  ");
   lcd.setCursor(0,1);
   lcd.print("  Reminder time ");
    delay(2000);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Enter Time 1");
    defualt();
    time(1);
    delay(1000);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Enter Time 2");
    defualt();
    delay(1000);
    time(2);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Enter Time 3");
    defualt();    
time(3);
     lcd.setCursor(0,0);
   lcd.print("Medicin reminder");
   lcd.setCursor(0,1);
   lcd.print("  time has set  ");
    delay(2000);
 }
 lcd.clear();
 lcd.setCursor(0,0);
 lcd.print("Time:");
 lcd.setCursor(6,0);
 lcd.print(HOUR=now.hour(),DEC); 
 lcd.print(":");
 lcd.print(MINUT=now.minute(),DEC);
 lcd.print(":");
 lcd.print(SECOND=now.second(),DEC);
 lcd.setCursor(0,1);
 lcd.print("Date: ");
 lcd.print(now.day(),DEC);
 lcd.print("/");
 lcd.print(now.month(),DEC);
 lcd.print("/");
 lcd.print(now.year(),DEC);
 match();
 delay(200);
}

void defualt()
{
  lcd.setCursor(0,1);
  lcd.print(HOUR);
  lcd.print(":");
  lcd.print(MINUT);
  lcd.print(":");
  lcd.print(SECOND);
}

/*Function to set alarm time and feed time into Internal eeprom*/

void time(int x)  
{
  int temp=1,minuts=0,hours=0,seconds=0;
    while(temp==1)
    {
     if(digitalRead(INC)==0)
     {
      HOUR++;
      if(HOUR==24)
      {
       HOUR=0;
      }
      while(digitalRead(INC)==0);
     }     
lcd.clear();
      lcd.setCursor(0,0);
    lcd.print("Enter Time ");
   lcd.print(x); 
    lcd.setCursor(0,1);
    lcd.print(HOUR);
    lcd.print(":");
    lcd.print(MINUT);
    lcd.print(":");
    lcd.print(SECOND);
    delay(100);
    if(digitalRead(next)==0)
    {
      hours1=HOUR;
      EEPROM.write(add++,hours1);
     temp=2;
     while(digitalRead(next)==0);
    }
    } 
    while(temp==2)
    {     
if(digitalRead(INC)==0)
     {
      MINUT++;
      if(MINUT==60)
      {MINUT=0;}
      while(digitalRead(INC)==0);
     }
      lcd.clear();
      lcd.setCursor(0,0);
    lcd.print("Enter Time ");
   lcd.print(x); 
    lcd.setCursor(0,1);
    lcd.print(HOUR);
    lcd.print(":");
    lcd.print(MINUT);
    lcd.print(":");
    lcd.print(SECOND);
    delay(100);
      if(digitalRead(next)==0)
      {
       minut=MINUT;
       EEPROM.write(add++, minut);
       temp=0;
       while(digitalRead(next)==0);
      }
    }
    delay(1000);
}


/* Function to chack medication time */

void match()
{
  int tem[17];
  for(int i=11;i<17;i++)
  {
    tem[i]=EEPROM.read(i); 
 }
  if(HOUR == tem[11] && MINUT == tem[12]) 
  {
   beep1();
   beep1();
   lcd.setCursor(0,0);
   lcd.print("  Take Group One  ");
   lcd.setCursor(0,1);
   lcd.print("     Medicine     ");
   beep1();
   beep1();
   beep1();
   beep1();
  }

   if(HOUR == tem[13] && MINUT == tem[14])
   {
      beep2();
   beep2();
    lcd.setCursor(0,0);
   lcd.print("  Take Group Two  ");
   lcd.setCursor(0,1);
   lcd.print("     Medicine     ");
    beep2();
   beep2();
   beep2();
   beep2();
   }


   if(HOUR == tem[15] && MINUT == tem[16] )
   { 
   beep3();
   beep3();
    lcd.setCursor(0,0);
   lcd.print("Take Group Three ");
   lcd.setCursor(0,1);
   lcd.print("     Medicine    ");
   beep3();
   beep3();
   beep3();
   beep3();
   }
}
/* function to buzzer indication */

void beep1()
{
   digitalWrite(buzzer,HIGH);
   digitalWrite(led1, HIGH);
   delay(5000);
   digitalWrite(buzzer, LOW);
   delay(5000);
   digitalWrite(led1,LOW);
   delay(5000);
}
void beep2()
{
   digitalWrite(buzzer,HIGH);
   digitalWrite(led2,HIGH);
   delay(5000);
   digitalWrite(buzzer, LOW);
   delay(5000);
   digitalWrite(led2,LOW);
   delay(5000);
}
void beep3()
{
   digitalWrite(buzzer,HIGH);
   digitalWrite(led3,HIGH);
   delay(5000);
   digitalWrite(buzzer, LOW);
   delay(5000);
   digitalWrite(led3,LOW);
   delay(5000);
}
