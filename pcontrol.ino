int ENA=6;
int IN1=7;
int IN2=5;
int IN3=4;
int IN4=2;
int ENB=3;
int vl=130;
int vr=130;
double pre_error=0;
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
  delay(2000);
  MotorWriting(-150,-150);
  delay(2000);
  MotorWriting(-150,150);
  delay(2000);
  MotorWriting(150,-150);
  delay(2000);
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
}

void loop() {
  MotorWriting(vl,vr);
  int l2=digitalRead(A1);
  int l1=digitalRead(A2);
  int m=digitalRead(A3);
  int r1=digitalRead(A4);
  int r2=digitalRead(A5);
  double w1=1;
  double w2=2;
//  if(A5==1 && A1+A2+A3+A4==0){vl = 180;vr = -150;}
//  else if(A1==1 && A2+A3+A4+A5==0){vl = -150;vr = 180;}
//  else{
    double error=(-1)*l2*w2-l1*w1+r1*w1+r2*w2+0.5*(w1+w2)*(l1+l2==2)+0.5*w1*(m+l1==2)-0.5*(w1+w2)*(r1+r2==2)-0.5*w1*(m+r1==2);
  
   
    int corr=80*error;
    int v_m=15;
    vl=v_m+corr;
    vr=v_m-corr;
  
    if (vl>255)vl=255;
    else if(vl>0&&vl<95)vl=95;
    //else if(vl == 0)vl = -90;
    else if(vl<0&&vl>-95)vl=-95;
    else if(vl<-255)vl=-255;
  
    if (vr>255)vr=255;
    else if(vr>0&&vr<95)vr=95;
    //else if(vr == 0) vr = -80;
    else if(vr<0&&vr>-95)vr=-95;
    else if(vr<-255)vr=-255;
//  }

}
