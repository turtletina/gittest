int ENA=6;
int IN1=7;
int IN2=5;
int IN3=4;
int IN4=2;
int ENB=3;
#define analogPin1 A1 //最左
#define analogPin2 A2
#define analogPin3 A3
#define analogPin4 A4
#define analogPin5 A5 //最右
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
void MotorCheck(){
  MotorWriting(150,150);
  
}

void setup() {
  // put your setup code here, to run once:
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
  
}

void loop() {
  // put your main code here, to run repeatedly:
   
  /*Serial.print("sensor1:");
  Serial.println(sensorValue1);
  Serial.print("sensor2:");
  Serial.println(sensorValue2);
  Serial.print("sensor3:");
  Serial.println(sensorValue3);
  Serial.println("sensor4:");
  Serial.print(sensorValue4);
  Serial.println("sensor5:");
  Serial.print(sensorValue5); 
  */ 
  int sensorValue1=digitalRead(A1);
  int sensorValue2=digitalRead(A2);
  int sensorValue3=digitalRead(A3);
  int sensorValue4=digitalRead(A4);
  int sensorValue5=digitalRead(A5);
  if(sensorValue1==1&&sensorValue2==0&&sensorValue3==0&&sensorValue4==0&&sensorValue5==0){  //大左轉
    MotorWriting(-150,180);
  }
  else if(sensorValue1==0&&sensorValue2==1&&sensorValue3==0&&sensorValue4==0&&sensorValue5==0){ //微左轉
    MotorWriting(-130,140);
  }
  else if(sensorValue1==0&&sensorValue2==0&&sensorValue3==1&&sensorValue4==0&&sensorValue5==0){ //直進
    MotorWriting(130,130);
  }
  else if(sensorValue1==0&&sensorValue2==0&&sensorValue3==0&&sensorValue4==1&&sensorValue5==0){ //微右轉
    MotorWriting(140,-130);
  }
  else if(sensorValue1==0&&sensorValue2==0&&sensorValue3==0&&sensorValue4==0&&sensorValue5==1){ //大右轉
    MotorWriting(180,-150);
  }
  else if(sensorValue1==1&&sensorValue2==1&&sensorValue3==0&&sensorValue4==0&&sensorValue5==0){ //左轉
    MotorWriting(-130,160);
  }
  else if(sensorValue1==0&&sensorValue2==1&&sensorValue3==1&&sensorValue4==0&&sensorValue5==0){ //微微左轉
    MotorWriting(-50,140);
  }
  else if(sensorValue1==0&&sensorValue2==0&&sensorValue3==1&&sensorValue4==1&&sensorValue5==0){ //微微右轉
    MotorWriting(140,-50);
  }
   else if(sensorValue1==0&&sensorValue2==0&&sensorValue3==0&&sensorValue4==1&&sensorValue5==1){ //右轉
    MotorWriting(160,-130);
  }
  else if(sensorValue1==0&&sensorValue2==1&&sensorValue3==1&&sensorValue4==1&&sensorValue5==0){ 
    MotorWriting(130,130);
  }
  
}
