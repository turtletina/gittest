#include<SPI.h>
#include<MFRC522.h>
//#include "motor.h"
#define RST_PIN 9
#define SS_PIN  10
MFRC522 *mfrc522;
int ENA=6;
int IN1=7;
int IN2=5;
int IN3=4;
int IN4=2;
int ENB=3;
int vl=130;
int vr=130;
int t = 0;
double pre_error = 0;
double derror = 0;
int sensorValue1=digitalRead(A1);
int sensorValue2=digitalRead(A2);
int sensorValue3=digitalRead(A3);
int sensorValue4=digitalRead(A4);
int sensorValue5=digitalRead(A5);
//藍芽腳位與程式庫
#include <SoftwareSerial.h>
SoftwareSerial BT (8, A0);



int n = 0;
int n_act = 0;
int reading = 1;
char action[13]={'1','1','1','1','3','2','1','3','4','3','2','1','e'};
int count_action=0;
bool getting_action=true;
#define analogPin1 A1 //最左
#define analogPin2 A2
#define analogPin3 A3
#define analogPin4 A4
#define analogPin5 A5 //最右



void setup() {
  pinMode(ENA,OUTPUT);
  pinMode(IN1,OUTPUT);
  pinMode(IN2,OUTPUT);
  pinMode(IN3,OUTPUT);
  pinMode(IN4,OUTPUT);
  pinMode(ENB,OUTPUT);
  pinMode(A1,INPUT);
  pinMode(A2,INPUT);
  pinMode(A3,INPUT);
  pinMode(A4,INPUT);
  pinMode(A5,INPUT);
  Serial.begin(9600);
  SPI.begin();
  BT.begin(9600);
  mfrc522 = new MFRC522(SS_PIN, RST_PIN);
  mfrc522 -> PCD_Init();
  Serial.println(F("Read UID on a MIFARE PICC:"));
  get_action();
  
}

void MotorWriting(double VL,double VR ){
  if(VL>=0)analogWrite(ENA, VL); //左輪
  else analogWrite(ENA, VL*(-1));
  if(VR>=0)analogWrite(ENB, VR); //右輪
  else analogWrite(ENB, VR*(-1));
  
  if(VL>=0){
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
  }
  else {
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
  }
  
  if(VR>=0){
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
  }
  else {
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
  }
}
void usuallydrive(){
  
  MotorWriting(vl,vr);
  int l2=digitalRead(A1);
  int l1=digitalRead(A2);
  int m=digitalRead(A3);
  int r1=digitalRead(A4);
  int r2=digitalRead(A5);
  double w1=1;
  double w2=2;
  double error=(-1)*l2*w2-l1*w1+r1*w1+r2*w2+0.5*(w1+w2)*(l1+l2==2)+0.5*w1*(m+l1==2)-0.5*(w1+w2)*(r1+r2==2)-0.5*w1*(m+r1==2);
  
  if(t==0)t++;
  else derror = error - pre_error;
  pre_error=error;
  
  
  int corr=80*error + 60*derror;
  int v_m=15;
  vl=v_m+corr;
  vr=v_m-corr;
  
  if (vl>255)vl=255;
  else if(vl>0&&vl<100)vl=100;
  else if(vl<0&&vl>-100)vl=-100;
  else if(vl<-255)vl=-255;
  
  if (vr>255)vr=255;
  else if(vr>0&&vr<100)vr=100;
  else if(vr<0&&vr>-100)vr=-100;
  else if(vr<-255)vr=-255;
  
}

void advance(){
     MotorWriting(100,85);
     delay(230);
     sensorValue1=digitalRead(A1);
     sensorValue2=digitalRead(A2);
     sensorValue3=digitalRead(A3);
     sensorValue4=digitalRead(A4);
     sensorValue5=digitalRead(A5);
     while(sensorValue1+sensorValue2+sensorValue3+sensorValue4+sensorValue5 >=3){
       MotorWriting(100,85);  //130
       delay(10);
       sensorValue1=digitalRead(A1);
       sensorValue2=digitalRead(A2);
       sensorValue3=digitalRead(A3);
       sensorValue4=digitalRead(A4);
       sensorValue5=digitalRead(A5);
     }
     
  }
void turn_right(){
     MotorWriting(130,0);
     delay(800);
     sensorValue1=digitalRead(A1);
     sensorValue2=digitalRead(A2);
     sensorValue3=digitalRead(A3);
     sensorValue4=digitalRead(A4);
     sensorValue5=digitalRead(A5);
     while(sensorValue1+sensorValue2+sensorValue3+sensorValue4+sensorValue5 == 0){
       MotorWriting(130,0);  //130
       delay(10);
       sensorValue1=digitalRead(A1);
       sensorValue2=digitalRead(A2);
       sensorValue3=digitalRead(A3);
       sensorValue4=digitalRead(A4);
       sensorValue5=digitalRead(A5);
     }
     MotorWriting(0,0);
     delay(200);
  }
void turn_left(){
     MotorWriting(0,100);
     delay(650);
     sensorValue1=digitalRead(A1);
     sensorValue2=digitalRead(A2);
     sensorValue3=digitalRead(A3);
     sensorValue4=digitalRead(A4);
     sensorValue5=digitalRead(A5);
     while(sensorValue1+sensorValue2+sensorValue3+sensorValue4+sensorValue5 == 0){
       MotorWriting(0,130);  //130
       delay(10);
       sensorValue1=digitalRead(A1);
       sensorValue2=digitalRead(A2);
       sensorValue3=digitalRead(A3);
       sensorValue4=digitalRead(A4);
       sensorValue5=digitalRead(A5);
     }
     MotorWriting(0,0);
     delay(200);
  }
void big_turn(){
     find_uid();//找寶藏
     MotorWriting(130,0);
     delay(900);
     MotorWriting(0,0);
     delay(300);
     MotorWriting(-100,-100);
     delay(450);
     MotorWriting(0,0);
     delay(300);
     MotorWriting(130,0);
     delay(600); //600
     find_uid();//找寶藏
     sensorValue1=digitalRead(A1);
     sensorValue2=digitalRead(A2);
     sensorValue3=digitalRead(A3);
     sensorValue4=digitalRead(A4);
     sensorValue5=digitalRead(A5);
     while(sensorValue1+sensorValue2+sensorValue3+sensorValue4+sensorValue5 == 0){
      sensorValue1=digitalRead(A1);
      sensorValue2=digitalRead(A2);
      sensorValue3=digitalRead(A3);
      sensorValue4=digitalRead(A4);
      sensorValue5=digitalRead(A5);
      MotorWriting(130,0);  //130
      delay(10);
      }
     MotorWriting(0,0);
     delay(200);
     sensorValue1=digitalRead(A1);
     sensorValue2=digitalRead(A2);
     sensorValue3=digitalRead(A3);
     sensorValue4=digitalRead(A4);
     sensorValue5=digitalRead(A5);
     //避免重複讀死巷塊
     if(sensorValue1*sensorValue2*sensorValue3*sensorValue4*sensorValue5 == 1){
        MotorWriting(100,85);
        delay(200);
        while(sensorValue1+sensorValue2+sensorValue3+sensorValue4+sensorValue5 == 0){
          sensorValue1=digitalRead(A1);
          sensorValue2=digitalRead(A2);
          sensorValue3=digitalRead(A3);
          sensorValue4=digitalRead(A4);
          sensorValue5=digitalRead(A5);
          MotorWriting(160,0);  //130
          delay(10);
        }
      }
//     find_uid();//找寶藏
  }
void car_stop(){
  MotorWriting(0,0);
  delay(10000);
}

void bt_print_byte(int origin){
  int first = origin / 16;
  int second = origin % 16 ;
  //Serial.println(first);
  //Serial.println(second);
  char fir = first < 9 ? char(first)+'0':char(first-10)+'A';
  char sec = second < 9 ? char(second)+'0':char(second-10)+'A';
  //Serial.println(fir);
  //Serial.println(sec);
  BT.write(fir);
  //BT.write('\n');
  BT.write(sec);
  
}
  void find_uid(){
  while (mfrc522 -> PICC_IsNewCardPresent() && mfrc522 -> PICC_ReadCardSerial()) {
      byte *id = mfrc522->uid.uidByte;   // 取得卡片的UID
      byte idSize = mfrc522->uid.size;   // 取得UID的長度
      Serial.print("UID Size: ");       // 顯示卡片的UID長度值
      Serial.println(idSize);
      for (int i = 0; i < idSize; i++) {  // 逐一顯示UID碼
        Serial.print("id[");
        Serial.print(i);
        Serial.print("]: ");
        Serial.println(id[i]);
        //Serial.println(id[i]/16);
        //Serial.println(id[i]%16);
        Serial.println(id[i], HEX);       // 以16進位顯示UID值
        bt_print_byte(id[i]);
       
      }
      Serial.println();
      BT.write('\n');
      mfrc522->PICC_HaltA();  // 讓卡片進入停止模式
    } 
  return;
}
void get_action(){
  while(BT.available()){
      action[count_action]=char(BT.read());
      if(action[count_action]=='e'){
        getting_action=false;
        Serial.println(action);
      }
      count_action++;
      //Serial.println(action);
     } 
}
void car_action(char cmd){
  if(cmd=='1') advance();
  else if(cmd=='2') big_turn();
  else if(cmd=='3') turn_right();
  else if(cmd=='4') turn_left();
  else if(cmd=='e') car_stop();
  Serial.print("now we are doing:");
  Serial.println(cmd);
  }

  void find_line(){
      while(sensorValue1+sensorValue2+sensorValue3+sensorValue4+sensorValue5 == 0){
        if(n<8){MotorWriting(160,0);  //大右擺
          delay(100);
          MotorWriting(0,0);
          delay(200);
          sensorValue1=digitalRead(A1);
          sensorValue2=digitalRead(A2);
          sensorValue3=digitalRead(A3);
          sensorValue4=digitalRead(A4);
          sensorValue5=digitalRead(A5);
          n ++;
          if(sensorValue1+sensorValue2+sensorValue3+sensorValue4+sensorValue5 != 0) {
            break;
            n=0;
          }
        }
        else{
            MotorWriting(0,160);  //大左擺
            delay(100);
            MotorWriting(0,0);
            delay(200);
            sensorValue1=digitalRead(A1);
            sensorValue2=digitalRead(A2);
            sensorValue3=digitalRead(A3);
            sensorValue4=digitalRead(A4);
            sensorValue5=digitalRead(A5);
            n ++;
            if(sensorValue1+sensorValue2+sensorValue3+sensorValue4+sensorValue5 != 0) {
              break;
              n=0;
            }
        }
        if(n==8){
          MotorWriting(-100,-85);  //大左擺
          delay(300);
          MotorWriting(0,0);
          delay(200);
        }
    }
    usuallydrive();
  }
  void loop() {
    find_uid();
      find_line();
      //狀況一:遇到直行塊
      usuallydrive();
      //狀況二:遇到轉彎塊或死巷塊
      sensorValue1=digitalRead(A1);
      sensorValue2=digitalRead(A2);
      sensorValue3=digitalRead(A3);
      sensorValue4=digitalRead(A4);
      sensorValue5=digitalRead(A5);
      if(sensorValue1+sensorValue2+sensorValue3+sensorValue4+sensorValue5 >= 3){
        MotorWriting(100,85);
        delay(200);
        sensorValue1=digitalRead(A1);
        sensorValue2=digitalRead(A2);
        sensorValue3=digitalRead(A3);
        sensorValue4=digitalRead(A4);
        sensorValue5=digitalRead(A5);
        MotorWriting(0,0);
        delay(400);
        car_action(action[reading]);
        reading+=1;
        }
      
       
  
}
