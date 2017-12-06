#include <SoftwareSerial.h>
SoftwareSerial gsmSerial(11,10);
void setup() 
{
   Serial.begin(9600);
   pinMode(2,OUTPUT);//buzzer
   pinMode(3,INPUT_PULLUP);//motion sensor
   gsmSerial.begin(9600);
   gsmSerial.println("at+cmgf=1");
   delay(300);
   gsmSerial.println("at+cnmi=2,2,0,0,0");
   delay(300);
}
void sendSMS(String num,String msg)
{
 gsmSerial.println("AT+CMGS=\""+num+"\"");
 delay(150);
 gsmSerial.println(msg);
 delay(150);
 gsmSerial.print(char(26)); 
}
void loop() 
{
 while(gsmSerial.available())
 {
  String gsmDta=gsmSerial.readStringUntil('\r');
  Serial.print(gsmDta);
  gsmDta.trim();
  if(gsmDta.startsWith("+CMT:"))
  {
    gsmDta=gsmSerial.readStringUntil('\r');
    gsmDta.trim();
    gsmDta.toLowerCase();
    Serial.println("msg:"+gsmDta);
    if(gsmDta.startsWith("on")){
      if(digitalRead(3)==LOW)
      digitalWrite(2,HIGH);
      sendSMS("ENTER MOBILE NUMBER HERE","motion sensor is on");
    }
    else if(gsmDta.startsWith("off"))
    {
      digitalWrite(2,LOW);
      sendSMS("ENTER MOBILE NUMBER HERE","motion sensor is off");
    }
  } 
 }
}
