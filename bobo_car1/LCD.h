#include <LiquidCrystal_PCF8574.h>
#include <Wire.h>
LiquidCrystal_PCF8574 lcd(0x27); 
String bufferr="";
char msg;
int i;
//*********************************************//
void print_LCD(); // print the string on LCD
//*********************************************//
void print_LCD(){
  //Serial.println(13);
  bufferr="";
  lcd.setBacklight(255);
  lcd.home();
  while(BT.available()){
    lcd.clear();
    msg=char(BT.read());
    bufferr=bufferr+msg;
  }     
  if(bufferr.length()<=16){
    lcd.print(bufferr);
    lcd.setCursor(0, 0);
  }
  else if(bufferr.length()>=16 && bufferr.length()<=32){
    lcd.setCursor(0, 0);
    for(i=0;i<bufferr.length();i++){
      if(i<16){
       lcd.print(bufferr[i]);
       lcd.setCursor(i, 0); 
      }
      else{
        lcd.print(bufferr[i]);
        lcd.setCursor(i-16, 1); 
      }
    }
  }
  else{
    lcd.setCursor(0, 0);
    bufferr+=" ";
    lcd.print(bufferr);
    for(i=0;i<50;i++){
      lcd.scrollDisplayLeft();
      delay(500);
    }
  }
  wait=true;
} 
