#include<SPI.h>
#include<LoRa.h>

int counter=0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  while(!Serial);
  Serial.println("LoRa Transmitter");
  if(!LoRa.begin(866E6)){
    Serial.println("Starting LoRa failed!");
    while(1);
  }

}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.print("Sending packet: ");
  Serial.println(counter);
  
  LoRa.beginPacket();
  LoRa.print("Hello! Packet #");
  LoRa.print(counter);
  LoRa.endPacket();
  counter++;

  delay(5000);

}
