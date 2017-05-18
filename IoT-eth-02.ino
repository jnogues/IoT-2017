//file IoT-eth-02.ino
//Internet of Things, Institut Rambla Prim
//Jaume Nogues jnogues@gmail.com
// http://vps249990.ovh.net/iot
// http://vps249990.ovh.net/grav/
// http://jnogues.org

#define BLYNK_PRINT Serial
#include <SPI.h>
#include <Ethernet.h>//wiznet 5100
#include <BlynkSimpleEthernet.h>//wiznet 5100
#include <Adafruit_NeoPixel.h>
#include <Servo.h>
#define PIN 5 //pin dels neopixels
#define NUMPIXELS 1 //nombre de oixels
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

char auth[] = "elVostreToken";
//no podem tenir dos MAC igual a la xarxa!
byte arduino_mac[] = { 0xDE, 0xED, 0xBA, 0xFE, 0xFE, 0x19 };

BlynkTimer timer;
Servo myservo; 

boolean stateI2=0;
boolean prevStateI2=0;
boolean stateI8=0;
boolean prevStateI8=0;
boolean stateIA2=0;
boolean prevStateIA2=0;
boolean stateIA1=0;
boolean prevStateIA1=0;
boolean stateQ3=0;
boolean prevStateQ3=0;
boolean stateQ7=0;
boolean prevStateQ7=0;
boolean stateQA3=0;
boolean prevStateQA3=0;
boolean stateQ9=0;
boolean prevStateQ9=0;

int blynkIsDownCount=0;
unsigned int tempC=0;

int dimmer=0;
int red=0;
int green=0;
int blue=0;

byte servoPosition=90;

void setup()
{
  pinMode(2,INPUT);
  pinMode(8,INPUT);
  pinMode(A2,INPUT);
  pinMode(A1,INPUT);
  pinMode(3,OUTPUT);
  pinMode(7,OUTPUT);
  pinMode(A3,OUTPUT);
  pinMode(9,OUTPUT);
  analogRead(A4);
  pinMode(A5, OUTPUT);
  digitalWrite(A5,0);
  myservo.attach(6);//pin del servo
  myservo.write(servoPosition);

  // Debug console
  Serial.begin(115200);
  Serial.println("Comencem....");

  // You need specify one of this servers:
  //Blynk.begin(auth, arduino_mac);//cloud
  Blynk.begin(auth, "vps249990.ovh.net", 8442, arduino_mac);//rPrim server
  //Blynk.begin(auth, "blynk-cloud.com", 8442,  arduino_mac);//cloud
  //Blynk.begin(auth, IPAddress(192,168,1,100), 8442, arduino_mac);//IP server

   pixels.begin(); // This initializes the NeoPixel library.
   pixels.show(); // Initialize all pixels to 'off'

   timer.setInterval(300L, checkInputsOutputs);
   timer.setInterval(9000L, publishA0);
   timer.setInterval(30000L, reconnecting);
   timer.setInterval(5000L, publishTemperature);
}

void loop()
{
  if (Blynk.connected())
  {
    Blynk.run();
  }
   timer.run();  
}

void reconnecting()
{
  if (!Blynk.connected())
  {
    blynkIsDownCount++;
    BLYNK_LOG("blynk server is down! %d  times", blynkIsDownCount);
    Blynk.connect(5000);
  }
}

BLYNK_CONNECTED() 
{ 
 Blynk.syncAll();
}

void publishA0()
{
  int A0value=analogRead(A0);
  //Serial.println(A0value);
  Blynk.virtualWrite(V0,A0value);
}

//upTime
BLYNK_READ(15)
{
   unsigned long m=millis()/1000L;
   Blynk.virtualWrite(V15,m);
   BLYNK_LOG("millis()= %d ", m);
}

void publishTemperature()
{
  tempC=analogRead(A4);
  tempC = (500*tempC)/1024;
  Blynk.virtualWrite(V24,tempC);
  Serial.println(tempC);
  //BLYNK_LOG("t= %d ", tempC);
}

BLYNK_WRITE(23)
{
  int pushButtonV23 = param.asInt();
  if (pushButtonV23==1)
  {
    bool temp=digitalRead(3);
    if (temp){ digitalWrite(3,LOW); Blynk.virtualWrite(V3,0);}
    if (!temp){ digitalWrite(3,HIGH); Blynk.virtualWrite(V3,255);}
  } 
}

void checkInputsOutputs()
{
      stateI2=digitalRead(2);
      if (prevStateI2==0 && stateI2==1)
      {
        bool temp=digitalRead(3);
        if (temp){ digitalWrite(3,LOW); Blynk.virtualWrite(V3,0);}
        if (!temp){ digitalWrite(3,HIGH); Blynk.virtualWrite(V3,255);}
        prevStateI2=1;
      }
      if (prevStateI2==1 && stateI2==0)
      {
        prevStateI2=0;
      }

     stateI8=digitalRead(8);
     if (stateI8!=prevStateI8)
     {
     if (stateI8==0) Blynk.virtualWrite(V8,0); 
     if (stateI8==1) {Blynk.virtualWrite(V8,255);Blynk.email("elTeuMail@gmail.com", "Missatge de blynk", "I8 activa");}
     }
     prevStateI8=stateI8;

     stateIA2=digitalRead(A2);
     if (stateIA2!=prevStateIA2)
     {
     if (stateIA2==0) Blynk.virtualWrite(V12,0);
     if (stateIA2==1) {Blynk.virtualWrite(V12,255); Blynk.notify("Finestres Menjador Obertes!");}
     }
     prevStateIA2=stateIA2;

     stateIA1=digitalRead(A1);
     if (stateIA1!=prevStateIA1)
     {
     if (stateIA1==0) Blynk.virtualWrite(V11,0);
     if (stateIA1==1) Blynk.virtualWrite(V11,255);
     }
     prevStateIA1=stateIA1;

     stateQ3=digitalRead(3);
     if (stateQ3!=prevStateQ3)
     {
     if (stateQ3==1) Blynk.virtualWrite(V3,255);
     if (stateQ3==0) Blynk.virtualWrite(V3,0);
     }
     prevStateQ3=stateQ3;

     stateQ7=digitalRead(7);
     if (stateQ7!=prevStateQ7)
     {
     if (stateQ7==1) Blynk.virtualWrite(V7,255);
     if (stateQ7==0) Blynk.virtualWrite(V7,0);
     }
     prevStateQ7=stateQ7;

     stateQA3=digitalRead(A3);
     if (stateQA3!=prevStateQA3)
     {
     if (stateQA3==1) Blynk.virtualWrite(V13,255);
     if (stateQA3==0) Blynk.virtualWrite(V13,0);
     }
     prevStateQA3=stateQA3;

     stateQ9=digitalRead(9);
     if (stateQ9!=prevStateQ9)
     {
     if (stateQ9==1) Blynk.virtualWrite(V9,255);
     if (stateQ9==0) Blynk.virtualWrite(V9,0);
     }
     prevStateQ9=stateQ9;
}

BLYNK_WRITE(16)
{
  dimmer = param[0].asInt();
  for(int i=0;i<NUMPIXELS;i++)
  {
    pixels.setPixelColor(i, pixels.Color(red*dimmer/100,green*dimmer/100,blue*dimmer/100));
    pixels.show();
  }
}

BLYNK_WRITE(17)
{
  red = param[0].asInt();
  green = param[1].asInt();
  blue = param[2].asInt();
  //red=(red*dimmer)/100; green=(green*dimmer)/100; blue=(blue*dimmer)/100;
  for(int i=0;i<NUMPIXELS;i++)
  {
    pixels.setPixelColor(i, pixels.Color(red*dimmer/100,green*dimmer/100,blue*dimmer/100));
    pixels.show();
  }
}

BLYNK_WRITE(V14)
{
  servoPosition = param[0].asInt();
  myservo.write(servoPosition);
}
