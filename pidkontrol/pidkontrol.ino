int pot,denge,hata;
#include <LiquidCrystal.h>
const int rs = 30, en = 32, d4 = 34, d5 = 36, d6 = 38, d7 = 40;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
void setup() {
  lcd.begin(20, 4);
  pinMode(5,OUTPUT);
  pinMode(6,OUTPUT);
  pinMode(7,OUTPUT);
  pinMode(8,OUTPUT);
  pinMode(9,OUTPUT);
  pinMode(10,OUTPUT);
  pinMode(A0,INPUT);
  pinMode(A1,INPUT);
  Serial.begin(9600);
}

void loop() {
digitalWrite(7,HIGH);
digitalWrite(9,HIGH);
pot=analogRead(A0);
denge=analogRead(A1);
denge=map(denge,0,1023,0,18);
pot=map(pot,285,306,0,18);
Serial.println(denge);
Serial.println(pot);
  lcd.setCursor(0,1);
  lcd.print("kaptan gelen:");
  lcd.print(pot);
  lcd.setCursor(0,2);
 lcd.print("referans:");
 lcd.print(denge);
delay(1000);
if(pot>denge)
{
    analogWrite(5,0);
    //delay(100);
  for(int i=0;i<255;i++)
  {
    analogWrite(10,i);
    //delay(10);
  }
}
else if(pot<denge){
  
  
    
    analogWrite(10,0);
  //  delay(100);
  for(int i=0;i<255;i++)
  {
    analogWrite(5,i);
   // delay(10);
  }
}
else if(pot==denge)
{
  analogWrite(5,0);
   analogWrite(10,0);
  }
}
  
  
     //for(hiz=0;hiz<=255;hiz++)//ayar
     //{
    
       //analogWrite(5,255);
       //delay(50);//ayar
     
    // }
    // for(hiz=0;hiz<=255;hiz++)//ayar
//{
    
       //analogWrite(10,255);
       //delay(5000);//ayar
     
     //}
      //denge1=analogWrite(A0);
      //for(hiz=255;hiz>=0;hiz--)//ayar
   // {
//        analogWrite(5,0);
       //delay(50);//ayar
    // }
//for(hiz=255;hiz>=0;hiz--)//ayar
   // {
        //analogWrite(10,0);
      // delay(5000);//ayar
   //  }
        //do{
        //  denge2=analogWrite(A0);
         // analogWrite(yan,denge1-denge2);
          //delay(100);
          //}
          //while(denge2<=denge1)
      
 //analogWrite(ana,25);
 //delay(100);
  

