int ENA=7;
int IN1=6;
int IN2=5;
int IN3=4;
int IN4=3;
int ENB=2;
#define analogPin1 A1
#define analogPin2 A2
#define analogPin3 A3
#define analogPin4 A4
#define analogPin5 A5

void setup() {
  // put your setup code here, to run once:
  pinMode(ENA,OUTPUT);
  pinMode(IN1,OUTPUT);
  pinMode(IN2,OUTPUT);
  pinMode(IN3,OUTPUT);
  pinMode(IN4,OUTPUT);
  pinMode(ENB,OUTPUT);
  pinMode(ENB,OUTPUT);
  pinMode(analogPin1,INPUT);
  pinMode(analogPin2,INPUT);
  pinMode(analogPin3,INPUT);
  pinMode(analogPin4,INPUT);
  pinMode(analogPin5,INPUT);
  Serial.begin(9600);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  int sensorValue1=digitalRead(analogPin5);
  int sensorValue2=digitalRead(analogPin4);
  int sensorValue3=digitalRead(analogPin3);
  int sensorValue4=digitalRead(analogPin2);
  int sensorValue5=digitalRead(analogPin1);
  Serial.println("sensor1:");
  Serial.println(sensorValue1);
  Serial.println("sensor2:");
  Serial.println(sensorValue2);
  Serial.println("sensor3:");
  Serial.println(sensorValue3);
  Serial.println("sensor4:");
  Serial.println(sensorValue4);
  Serial.println("sensor5:");
  Serial.println(sensorValue5);  
  delay(500); 
  //前
  digitalWrite(ENA,HIGH);
  digitalWrite(ENB,HIGH);
  digitalWrite(IN1,HIGH);
  digitalWrite(IN2,LOW);
  digitalWrite(IN3,HIGH);
  digitalWrite(IN4,LOW);
  delay(2000);
  //后
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,HIGH);
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,HIGH);
  delay(2000);
  //左向後，右向前
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,HIGH);
  digitalWrite(IN3,HIGH);
  digitalWrite(IN4,LOW);
  delay(2000);
  //左向前，右向後
  digitalWrite(IN1,HIGH);
  digitalWrite(IN2,LOW);
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,HIGH);
  delay(2000);
  //左輪動，右輪停
  digitalWrite(IN1,HIGH);
  digitalWrite(IN2,LOW);
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,LOW);
  delay(2000);
  //右輪動，左輪停
   digitalWrite(IN1,LOW);
  digitalWrite(IN2,LOW);
  digitalWrite(IN3,HIGH);
  digitalWrite(IN4,LOW);
  delay(2000);

}
