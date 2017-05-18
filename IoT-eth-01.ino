//file IoT-eth-01.ino
//Internet of Things, Institut Rambla Prim
//Jaume Nogues jnogues@gmail.com
// http://vps249990.ovh.net/iot
// http://vps249990.ovh.net/grav
// http://jnogues.org

#define BLYNK_PRINT Serial //Aquesta linia cal comentar-la si utilitzem l'ENC28J60 per estalviar memoria
#include <SPI.h>
//Tria una d'aquestes dos llibreries segons l'ethernet shield que utilitzis
//#include <UIPEthernet.h>//ENC28J60
//#include <BlynkSimpleUIPEthernet.h>//ENC28J60
//#include <Ethernet.h>//wiznet 5100
//#include <BlynkSimpleEthernet.h>//wiznet 5100

char auth[] = "elTeuToken";
//no podem tenir dos MAC igual a la xarxa!
byte arduino_mac[] = { 0xDE, 0xED, 0xBA, 0xFE, 0xFE, 0x19 };

BlynkTimer timer;//Temporitzador per programar accions repetitives

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

int blynkIsDownCount=0;//per debug

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

  // Debug console
  Serial.begin(115200);
  Serial.println("Empezamos....");

  // You need specify one of this servers:
  //Blynk.begin(auth, arduino_mac);//cloud
  Blynk.begin(auth, "vps249990.ovh.net", 8442, arduino_mac);//rPrim server
  //Blynk.begin(auth, "blynk-cloud.com", 8442,  arduino_mac);//cloud
  //Blynk.begin(auth, IPAddress(192,168,1,100), 8442, arduino_mac);//IP server

   timer.setInterval(300L, checkInputsOutputs);
   timer.setInterval(9000L, publishA0);
   timer.setInterval(30000L, reconnecting);
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
  Blynk.virtualWrite(V0,A0value);
}

//upTime
BLYNK_READ(15)
{
   unsigned long m=millis()/1000L;
   Blynk.virtualWrite(V15,m);
   BLYNK_LOG("millis()= %d ", m);
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
