#include "pxt.h"

#include "MbitMoreRadio.h"


#include "MbitMoreSerial.h"

MbitMoreRadio::MbitMoreRadio(MbitMoreDevice &_mbitMore) : mbitMore(_mbitMore) {
   
uBit.messageBus.listen(MICROBIT_ID_RADIO, MICROBIT_RADIO_EVT_DATAGRAM, this, &MbitMoreRadio::onRadioreceived);
uBit.radio.enable();

 Radiosetgroup(0);
 Radiosetsignalpower(7);



}

void MbitMoreRadio::Radiosetsignalpower(int signalpower){

 uBit.radio.setTransmitPower(signalpower);


 



}


void MbitMoreRadio::Radiosetgroup(int group){

    uBit.radio.setGroup(group);
    


}



void MbitMoreRadio::sendrawpacket( uint8_t buf[],int len){
PacketBuffer b(buf,len);


uBit.radio.datagram.send(b);



}



void MbitMoreRadio::onRadioreceived( MicroBitEvent e){
     PacketBuffer b;
b = uBit.radio.datagram.recv();

int length = b.length();
uint8_t *bytes = b.getBytes();
int signal = b.getRSSI();
uint8_t signalbuf [4] ={ 
static_cast<uint8_t>(signal >> 24 && 0x100),
static_cast<uint8_t>(signal >>16 && 0x100) ,
static_cast<uint8_t>(signal >>8 && 0x100),
static_cast<uint8_t>(signal  && 0x100)
  };

uint8_t buf[36];

 memset(buf, 0, sizeof(buf));
  memcpy(buf, bytes, length);
  for (int i = 0 ;i<4;i++) {buf [32+i] = signalbuf[i];};



    


}

MbitMoreRadio::~MbitMoreRadio(){

}

