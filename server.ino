#include <WiFiUdp.h>
#include <ESP8266WiFi.h>

const char* ssid = "swarm";
const char* password = "bismillah";

IPAddress client1(192,168,4,2);
IPAddress client2(192,168,4,3);
IPAddress client3(192,168,4,4);

char start0= 'a';
char start1= 'b';
char start2= 'c';
char start3= 'e';
char stop0= 'd';

WiFiUDP Udp;
unsigned int localUdpPort = 4210;  // local port to listen on
unsigned int espPort= 1112;   //esp port
char incomingPacket[1024];  // buffer for incoming packets

void setup()
{
  Serial.begin(115200);
  Serial.println("create access point");
  WiFi.mode(WIFI_AP);
  while(!WiFi.softAP(ssid,password)){
    Serial.print('.');
    delay(100);
  }
  Serial.println("access point created");
  Serial.print("Now listening at IP, ");
  Serial.println(WiFi.localIP());
    
  Udp.begin(localUdpPort);
  Serial.print("UDP port, ");
  Serial.println(localUdpPort);
}

void loop()
{
  char buff;
  if(Serial.available()){
     buff= Serial.read(); 
     sendtoClient(client1,espPort,buff);
     sendtoClient(client2,espPort,buff);
     sendtoClient(client3,espPort,buff);
  }
  
  int packetSize = Udp.parsePacket();
  if (packetSize)
  {
    // receive incoming UDP packets //for debugging purpose
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
    //Serial.print("UDP packet contents: ");  //for debugging purpose
    Serial.println(incomingPacket);

    // send back a reply, to the IP address and port we got the packet from //for debugging purpose
    //Udp.beginPacket(Udp.remoteIP(), Udp.remotePort());
    //Udp.write(replyPacekt);
    //Udp.endPacket();
  }
}

void sendtoClient(IPAddress ip,unsigned int port,char a){
  Udp.beginPacket(ip,port);
  switch(a){
    case 'a':{
      for(int i=0;i<10;i++){      
        Udp.write(start0);
        delay(10);        
      }
    }
    break;
    case 'b':{
      for(int i=0;i<10;i++){
        Udp.write(start1);
        delay(10);        
      }      
    }
    break;
    case 'c':{
      for(int i=0;i<10;i++){
        Udp.write(start2);
        delay(10);        
      }      
    }
    break;
    case 'd':{
      for(int i=0;i<10;i++){
        Udp.write(stop0);
        delay(10);        
      }      
    }
    break;
    case 'e':{
      for(int i=0;i<10;i++){
        Udp.write(start3);
        delay(10);        
      }      
    }
    break;
  }
  Udp.endPacket();
}

