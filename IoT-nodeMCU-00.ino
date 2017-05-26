//file IoT-nodeMCU-00.ino
//Internet of Things, Institut Rambla Prim
//Jaume Nogues jnogues@gmail.com
//http://vps249990.ovh.net/iot/
//http://vps249990.ovh.net/grav/
//http://jnogues.org
#define BLYNK_PRINT Serial    // Comment this out to disable prints and save space

//configuracio wifi
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
char ssid[] = "ssid"; //xarxa wifi           
char pass[] = "password"; //password wifi
char auth[] = "elMeuToken";
char vpsServer[] = "vps249990.ovh.net";
//IPAddress ipServer (192, 168, 1, 222);//Servidor local

BlynkTimer timer; // Create a Timer object called "timer"! 

boolean state4=0;
boolean state5=0;
boolean state16=0;
boolean state14=0;
boolean state12=0;
boolean prevState14=0;
boolean prevState12=0;
boolean prevState4=0;
boolean prevState5=0;

void setup()
{
  Serial.begin(115200);
  Serial.println("Comencem..");

  Blynk.begin(auth, ssid, pass, vpsServer);//servidor rPrim
  //Blynk.begin(auth, ssid, pass, ipServer);//servidor local amb IP
  //Blynk.begin(auth, ssid, pass);//servidor cloud blynk

  pinMode(5, INPUT);
  pinMode(4, INPUT);
  pinMode(14, INPUT);
  pinMode(12, INPUT);
  pinMode(0,OUTPUT);
  pinMode(2,OUTPUT);
  pinMode(13,OUTPUT);
  pinMode(15,OUTPUT);
  pinMode(16,OUTPUT);//built in led
  digitalWrite(0,HIGH);
  digitalWrite(2,HIGH);
  digitalWrite(13,LOW);
  digitalWrite(15,LOW);
  digitalWrite(16,HIGH);
  timer.setInterval(300L, toggle);
}

void loop()
{
  Blynk.run();
  timer.run(); // SimpleTimer is working
}

void toggle()
{
  digitalWrite(16,state16);
  state16=!state16;
}

BLYNK_CONNECTED()
{
  Blynk.syncAll();
  Serial.println(".");//per debug
}
