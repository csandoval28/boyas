#include <SoftwareSerial.h>

#include <Dhcp.h>
#include <Dns.h>
#include <Ethernet.h>
#include <EthernetClient.h>
#include <EthernetServer.h>
#include <EthernetUdp.h>
#include <util.h>

#include <nRF24L01.h>

#include <RF24.h>
#include <RF24_config.h>
//tiene que ir ultimo
#include <printf.h>

/*
* Getting Started example sketch for nRF24L01+ radios
* This is a very basic example of how to send data from one node to another
* Updated: Dec 2014 by TMRh20
*/

#include <SPI.h>

SoftwareSerial BT(3,4);
RF24 radio(6, 7);

const uint64_t pipes[6] = { 0xF0F0F0F0E1LL, 0xF0F0F0F0D2LL,0xF0F0F0F0B2LL,0xF0F0F0F0A2LL,0xF0F0F0F0C2LL,0xF0F0F0F020LL};

typedef enum { role_ping_out = 1, role_pong_back } role_e;
const char* role_friendly_name[] = { "invalid", "Ping out", "Pong back"};
role_e role = role_ping_out; 
char replybuffer[255]; 


uint8_t readline(char *buff, uint8_t maxbuff, uint16_t timeout = 0);

struct dataStruct{
  unsigned long _micros;
  float value;
}myData;

void setup() {
  BT.begin(9600);
  Serial.begin(9600);
  Serial.println(F("RF24/examples/GettingStarted_HandlingData"));
  Serial.println(F("*** PRESS 'T' to begin transmitting to the other node"));
  
  radio.begin();
  radio.setRetries(15,15);
  printf_begin();
  // Set the PA Level low to prevent power supply related issues since this is a
 // getting_started sketch, and the likelihood of close proximity of the devices. RF24_PA_MAX is default.
  radio.setPALevel(RF24_PA_LOW);
  radio.printDetails();
  // Open a writing and reading pipe on each radio, with opposite addresses
    

  myData.value = 1.22;
  // Start the radio listening for data
  radio.startListening();
}




void loop() {

  delay(1000);
  
     radio.openReadingPipe(1,pipes[1]);
     radio.openReadingPipe(2,pipes[2]);
     radio.openReadingPipe(3,pipes[3]);
     radio.openReadingPipe(4,pipes[4]);
     radio.openReadingPipe(5,pipes[5]);
     radio.openReadingPipe(6,pipes[6]);
    if ( radio.available() )
    {
      
      
    
      
      char outBuffer[32];
      //bool done = false;
  
        
        while(radio.available()){
  radio.read( &outBuffer, sizeof(outBuffer) );
  printf(outBuffer);

  BT.println(outBuffer);
  Serial.println(outBuffer);


      }

    
      radio.startListening();
    }
  
  
  
  
  
  
}

