#include "pxt.h"

#include "MbitMoreRadio.h"

static MbitMoreRadio *Radio;

MbitMoreRadio::MbitMoreRadio(MbitMoreDevice &_mbitMore) : mbitMore(_mbitMore) {
   
//uBit.messageBus.listen(MICROBIT_ID_RADIO, MICROBIT_RADIO_EVT_DATAGRAM, this, &MbitMoreRadio::onRadioreceived);
uBit.radio.enable();
uBit.display.scrollAsync("set");
 Radiosetgroup(0);
 Radiosetsignalpower(7);


}

void MbitMoreRadio::Radiosetsignalpower(int signalpower){

 uBit.radio.setTransmitPower(signalpower);
 uBit.display.scrollAsync("signal");

 



}


void MbitMoreRadio::Radiosetgroup(int group){

    uBit.radio.setGroup(group);
     uBit.display.scrollAsync("group");


}



void MbitMoreRadio::sendrawpacket( uint8_t buf[],int len){
PacketBuffer b(buf,len);


uBit.radio.datagram.send(b);



}


void MbitMoreRadio::onRadioreceived( MicroBitEvent e){


    


}

MbitMoreRadio::~MbitMoreRadio(){

}

