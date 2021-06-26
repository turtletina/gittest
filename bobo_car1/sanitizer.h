
//*********************************************//
void sanitize(); // control the servo to turn 180 so the sanitizer cab be activated
//*********************************************//


void sanitize() {
 Serial.println(123);
 for(int i=180;i>=0;i-=1){
  myservo.write(i);
 }
 wait=true;
}
