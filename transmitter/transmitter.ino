#include<SPI.h>
#include<LoRa.h>

struct PacketHeader{
  byte destinationAddress;
  byte sourceAddress;
  byte messageType;
  byte payloadLength;
  byte sequenceNumber;
  byte checksum;
};

// int counter=0;

byte calculateChecksum(const char* payload,byte payloadSize){
  byte sum=0;
  for(int i=0;i<payloadSize;i++){
    sum+=payload[i];
  }
  return sum;
}

byte messageCounter=0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  while(!Serial);
  Serial.println("LoRa Protocol Transmitter");
  if(!LoRa.begin(866E6)){
    Serial.println("Starting LoRa failed!");
    while(1);
  }

}

void loop() {
  // put your main code here, to run repeatedly:
  char payload[]="Hello, it's a test msg.";
  byte payloadSize=sizeof(payload);

  PacketHeader header;
  header.destinationAddress=0x02;
  header.sourceAddress=0x01;
  header.messageType=0x01;
  header.sequenceNumber=messageCounter;
  header.payloadLength=payloadSize;
  header.checksum=calculateChecksum(payload,payloadSize);

  byte packetBuffer[sizeof(header)+payloadSize];
  memcpy(packetBuffer,&header,sizeof(header));
  memcpy(packetBuffer+sizeof(header),payload,payloadSize);

  Serial.print("Sending packet: #");
  Serial.println(messageCounter);
  
  LoRa.beginPacket();
  LoRa.write(packetBuffer,sizeof(packetBuffer));
  LoRa.endPacket();
  Serial.println("Sent!");
  messageCounter++;

  delay(5000);

}
