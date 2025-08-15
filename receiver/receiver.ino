#include <SPI.h>
#include <LoRa.h>

void setup(){
  Serial.begin(115200);
  while(!Serial);
  Serial.println("LoRa Receiver");
  if(!LoRa.begin(866E6)){
    Serial.println("Starting LoRa failed!");
    while(1);
  }
}

void loop(){
  int packetSize=LoRa.parsePacket();
  if(packetSize){
    Serial.print("Received Packet: ");
    while(LoRa.available()){
      Serial.print((char)LoRa.read());
    }
    Serial.print(" with RSSI ");
    Serial.println(LoRa.packetRssi());
  }
}