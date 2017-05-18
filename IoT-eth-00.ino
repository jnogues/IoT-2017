//file IoT-eth-00.ino
//Internet of Things, Institut Rambla Prim
//Jaume Nogues jnogues@gmail.com
//http://vps249990.ovh.net/iot/
// http://vps249990.ovh.net/grav/
// http://jnogues.org

#define BLYNK_PRINT Serial // Comment this out to disable prints and save space
#include <SPI.h>
//Tria una d'aquestes dos llibreries segons l'ethernet shield que utilitzis
//#include <UIPEthernet.h>//ENC28J60
//#include <BlynkSimpleUIPEthernet.h>//ENC28J60
//#include <Ethernet.h>//wiznet 5100
//#include <BlynkSimpleEthernet.h>//wiznet 5100

char auth[] = "elTeuToken";//servidor blynk
byte arduino_mac[] = { 0xDE, 0xED, 0xBA, 0xFE, 0xFE, 0xED };
//CAL CANVIAR AQUESTA MAC PER UN ALTRE
//NO PODEN HAVER 2 IGUALS A LA MATEIXA XARXA

//You need specify one of this servers:
//Blynk.begin(auth, arduino_mac);//cloud
Blynk.begin(auth, "vps249990.ovh.net", 8442, arduino_mac);//rPrim server
//Blynk.begin(auth, "blynk-cloud.com", 8442, arduino_mac);//cloud
//Blynk.begin(auth, IPAddress(192,168,1,100), 8442, arduino_mac);//IP server

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

Serial.begin(115200);

}

void loop()
{
        Blynk.run();
}
BLYNK_CONNECTED()
{
        Blynk.syncAll();
        Serial.println(".");//per debug
}
