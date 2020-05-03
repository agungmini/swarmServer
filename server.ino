#include <WiFiUdp.h>
#include <ESP8266WiFi.h>

const char* ssid = "swarm";
const char* password = "bismillah";

IPAddress staticIP(192,168,4,1);
IPAddress gateway(192,168,4,1);
IPAddress subnet(255,255,255,0);

IPAddress client1(192,168,4,2);
IPAddress client2(192,168,4,3);
IPAddress client3(192,168,4,4);

char start0;
char start1;
char start2;
char start3;
char stop0;

WiFiUDP Udp;
unsigned int localUdpPort = 4210;  // local port to listen on
char incomingPacket[255];  // buffer for incoming packets
char  replyPacekt[] = "Received";  // a reply string to send back

void setup()
{
  Serial.begin(115200);
  Serial.println();
  WiFi.softAP(ssid,password);
  Udp.begin(localUdpPort);
  Serial.print("Now listening at IP, ");
  Serial.println(WiFi.localIP());
  Serial.print("UDP port, ");
  Serial.print(localUdpPort);
}

void loop()
{
  char buff;
  if(Serial.available()){
     buff= Serial.read();
  }

  switch(buff){
 
  }
  
  int packetSize = Udp.parsePacket();
  if (packetSize)
  {
    // receive incoming UDP packets
    //Serial.print("Received ");
    //Serial.print(packetSize);
    //Serial.print(", bytes from ");
    //Serial.print(Udp.remoteIP());
    //Serial.print(", at port ");
    //Serial.println(Udp.remotePort());

    int len = Udp.read(incomingPacket, 255);
    if (len > 0)
    {
      incomingPacket[len] = 0;
    }
    //Serial.print("UDP packet contents: ");
    Serial.println(incomingPacket);

    // send back a reply, to the IP address and port we got the packet from
    Udp.beginPacket(Udp.remoteIP(), Udp.remotePort());
    Udp.write(replyPacekt);
    Udp.endPacket();
  }
}
