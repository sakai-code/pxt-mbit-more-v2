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

uint8_t buf[36];

 memset(buf, 0, sizeof(buf));
  memcpy(buf, bytes, length);


    


}

MbitMoreRadio::~MbitMoreRadio(){

}

