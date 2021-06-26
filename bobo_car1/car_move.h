int vl=130;
int vr=130;
int t = 0;
double pre_error = 0;
double derror = 0;
//*********************************************//
void MotorWriting(double VL,double VR ); //set the power of left and right motor. positive is clockwise,negative is counterclockwise. 
void usuallydrive(); //Let car go on the black line automatically.
void advance(); //car go ahead after visiting a node 
void turn_right(); //car turn right until it reach the black line after visiting a node 
void turn_left(); //car turn left until it reach the black line after visiting a node 
void big_turn(); //car tuen for 180 degree after visiting a node 
void find_line(); // if the car deviate from track this will help it find the track again
void car_stop(); //set power of motor to zero and let the system back to wait status
void car_action(char cmd); //when visiting a node it will decide next action of the car
void get_action(); //when system start receiving code by BFS it will store the information
void car_go();
//*********************************************//
void car_go(){
  while(action[reading-1]!='e'){
      usuallydrive();
      sensorValue1=digitalRead(A1);
      sensorValue2=digitalRead(A2);
      sensorValue3=digitalRead(A3);
      sensorValue4=digitalRead(13);
      sensorValue5=digitalRead(12);
      
      if(sensorValue1+sensorValue2+sensorValue3+sensorValue4+sensorValue5 >= 4){
        MotorWriting(100,85);
        delay(200);
        sensorValue1=digitalRead(A1);
        sensorValue2=digitalRead(A2);
        sensorValue3=digitalRead(A3);
        sensorValue4=digitalRead(13);
        sensorValue5=digitalRead(12);
        MotorWriting(0,0);
        delay(400);
        car_action(action[reading]);
        reading+=1;
        }
  }
}
void get_action(){
  //Serial.println("abc");
  while(wait==false){
    if(BT.available()){
      action[count_action]=char(BT.read());
      Serial.println(action[count_action]);
      if(action[count_action]==','){
        continue;
      }
      if(action[count_action]=='e'){
       // now_dir=BT.read();
       // now_pos=BT.read();
        count_action=0;
        Serial.println(action);
        reading=1;
        car_go();
        wait=true;
        break;
      }
      count_action++;
      //Serial.println(action);
     } 
  }
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
     while(sensorValue1+sensorValue2+sensorValue3+sensorValue4+sensorValue5 == 0||sensorValue1+sensorValue2+sensorValue3+sensorValue4+sensorValue5 >= 3){
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
int n = 0;
void find_line(){
      sensorValue1=digitalRead(A1);
      sensorValue2=digitalRead(A2);
      sensorValue3=digitalRead(A3);
      sensorValue4=digitalRead(A4);
      sensorValue5=digitalRead(A5);
      while((sensorValue1+sensorValue2+sensorValue3+sensorValue4+sensorValue5) == 0){
        if(n<8){
          MotorWriting(160,0);  //大右擺
          delay(100);
          MotorWriting(0,0);
          delay(200);
          sensorValue1=digitalRead(A1);
          sensorValue2=digitalRead(A2);
          sensorValue3=digitalRead(A3);
          sensorValue4=digitalRead(A4);
          sensorValue5=digitalRead(A5);
          n ++;
          if((sensorValue1+sensorValue2+sensorValue3+sensorValue4+sensorValue5) != 0) {
            n=0;
            break;
            
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
            if((sensorValue1+sensorValue2+sensorValue3+sensorValue4+sensorValue5) != 0) {
              n=0;
              break;
             
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
void big_turn(){
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
     if(sensorValue1+sensorValue2+sensorValue3+sensorValue4+sensorValue5 >= 4){
        MotorWriting(100,85);
        delay(200);
        find_line();
      }
}
void car_stop(){
  MotorWriting(0,0);
  wait=true;
}
void car_action(char cmd){
  if(cmd=='a') advance();
  else if(cmd=='u') big_turn();
  else if(cmd=='r') turn_right();
  else if(cmd=='l') turn_left();
  else if(cmd=='e')car_stop();
  Serial.print("now we are doing:");
  Serial.println(cmd);
}
